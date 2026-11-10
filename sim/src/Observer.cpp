/*
** ------- Preprocessor directives -------
*/ 
#include "Observer.hh"
#include "Model.hh"
#include "CelestialBody.hh"
#include "InputParser.hh"
#include "Constants.hh"
#include "CoordinateTransform.hh"
#include "Spacecraft.hh"
#include <string>	// for std::string
#include <cstddef>  // for std::size_t
#include <cstdio>	// for printf
#include <cstdlib>  // for std::exit()
#include <cmath>	// for std::sqrt(), std::acos(), etc.

/*
** -------------- Constants ---------------
*/ 

/*
** -------- Forward Declarations ----------
*/ 

/*
** --------- Namespace directives ---------
*/ 
using namespace Constants;
using namespace CoordinateTransform;

/*
** ----------- Class Definition ------------
*/ 
Observer::Observer(const std::string& name, json inputFileData, Earth* pEarth) :
	Model( name ), _pEarth { pEarth }
{

	// get observer initial state
	gdLat = inputFileData["gdLat"].get<double>() * DEG2RAD;
	lon = inputFileData["lon"].get<double>() * DEG2RAD;
	alt = inputFileData["alt"].get<double>();
	double heading { inputFileData["heading"].get<double>() * DEG2RAD };
	double speed { inputFileData["speed"].get<double>() * M2KM };

	// build initial state
	RofOwrtCexpE = {
		( _pEarth->getGeoidHeight( gdLat ) + alt ) * std::cos( gdLat ) * std::cos( lon ),
		( _pEarth->getGeoidHeight( gdLat ) + alt ) * std::cos( gdLat ) * std::sin( lon ),
		( _pEarth->getGeoidHeight( gdLat ) * ( 1.0 - Earth::eccentricity * Earth::eccentricity ) + alt ) * std::sin( gdLat )
	};
	Vector3 VofOwrtEexpN { 
		speed * std::cos( heading ),
		speed * std::sin( heading ),
		0.0
	};
	FrameTransform CfromNtoE;
	CfromNtoE.setN2E( gdLat, lon );
	VofOwrtEexpE = CfromNtoE.getDCM() * VofOwrtEexpN;

	// set output flag
	_outputFlag = inputFileData["outputFlag"].get<bool>();

	// populate initial values
	updateStateDependents();
}

void Observer::initModel()
{
	// NOTE initModel() is executed when Model registered to Integrator

	// register ECEF states to be integrated
	registerStates(RofOwrtCexpE, VofOwrtEexpE);

	// register outputs with integrator
	registerOutput("RofOwrtCexpI", RofOwrtCexpI);
	registerOutput("RofOwrtCexpE", RofOwrtCexpE);
	registerOutput("VofOwrtEexpE", VofOwrtEexpE);
	registerOutput("VofOwrtIexpI", VofOwrtIexpI);

	registerOutput("gcLat", gcLat);
	registerOutput("gdLat", gdLat);
	registerOutput("lon", lon);
	registerOutput("alt", alt);
	registerOutput("st", st);

	// set initialized flag
	_initialized = true;

}

// called after state (position and velocity) is updated to next timestep
void Observer::updateStateDependents()
{
	RofOwrtCexpI = _pEarth->getCfromEtoI() * RofOwrtCexpE;
	VofOwrtIexpI = _pEarth->getCfromEtoI() * ( VofOwrtEexpE + cross( _pEarth->WofEwrtIexpE, RofOwrtCexpE ) );
	
	// get longitude, latitude, altitude, and sidereal time
	gcLat = getGeocentricLatitude( RofOwrtCexpE, RofOwrtCexpE.mag() );
	gdLat = getGeodeticLatitude( gcLat );
	lon = getLongitude( RofOwrtCexpE );
	alt = getAltitude( RofOwrtCexpE, gdLat );
	st = getSiderealTime( RofOwrtCexpI );

	// set NED tranformation
	CfromItoN.setI2N( gdLat, st );
	RofOwrtCexpN = CfromItoN.getDCM() * RofOwrtCexpI;
	VofOwrtIexpN = CfromItoN.getDCM() * VofOwrtIexpI;

	// set tropocentric transformation
	CfromItoT.setI2T( gdLat, st );
	RofOwrtCexpT = CfromItoT.getDCM() * RofOwrtCexpI;
	VofOwrtIexpT = CfromItoT.getDCM() * VofOwrtIexpI;

	Vector3 RofBwrtOexpN { ZERO_VECTOR3 };

	for ( std::size_t i { 0 }; i < _numSpacecraft; ++i )
	{
		// get range vectors
		RofBwrtOexpIArray[i] = _pSpacecraftArray[i]->getSpacecraftBody()->RofBwrtCexpI - RofOwrtCexpI;

		// get right ascension and declination of range vector
		raArray[i] = std::atan2( RofBwrtOexpIArray[i][1], RofBwrtOexpIArray[i][0] );
		declArray[i] = std::asin( RofBwrtOexpIArray[i][2] / RofBwrtOexpIArray[i].mag() );

		// get azimuth and elevation
		RofBwrtOexpN = CfromItoN.getDCM() * _pSpacecraftArray[i]->getSpacecraftBody()->RofBwrtCexpI - RofOwrtCexpN;
		azArray[i] = std::atan2( RofBwrtOexpN[1], RofBwrtOexpN[0] );
		elArray[i] = std::asin( -1.0 * RofBwrtOexpN[2] / RofBwrtOexpN.mag() );
	}
}

// called after state dependents are updated to next timestep
void Observer::updateDerivs()
{
	// assume constant velocity with respect to ECEF
}

// register spacecraft to track
void Observer::registerSpacecraft(Spacecraft* pSpacecraft)
{
	if ( nullptr == pSpacecraft )
	{
		printf("Error: Cannot register null Spacecraft to Observer!\n");
		std::exit(EXIT_FAILURE);
	}

	// check if model has already been registered
	for ( std::size_t i { 0 }; i < _numSpacecraft; ++i )
	{
		if ( pSpacecraft == _pSpacecraftArray[i] )
		{
			printf("Error: Spacecraft %s already registered with Observer %s!\n", (pSpacecraft->getName()).c_str(), getName().c_str());
			std::exit(EXIT_FAILURE);
		}
	}

	// check if max number of Spacecraft reached
	if ( _numSpacecraft >= MAX_SPACECRAFT_TO_TRACK )
	{
		printf("Error: Maximum number of tracked Spacecraft reached!\n");
		std::exit(EXIT_FAILURE);
	}

	// register variables to output
	registerOutput( getName() + "_to_" + pSpacecraft->getName() + "_RofBwrtOexpI", RofBwrtOexpIArray[_numSpacecraft] );
	registerOutput( getName() + "_to_" + pSpacecraft->getName() + "_ra", raArray[_numSpacecraft] );
	registerOutput( getName() + "_to_" + pSpacecraft->getName() + "_decl", declArray[_numSpacecraft] );
	registerOutput( getName() + "_to_" + pSpacecraft->getName() + "_az", azArray[_numSpacecraft] );
	registerOutput( getName() + "_to_" + pSpacecraft->getName() + "_el", elArray[_numSpacecraft] );

	// add spacecraft to tracker
	_pSpacecraftArray[_numSpacecraft] = pSpacecraft;
	++_numSpacecraft;
}
