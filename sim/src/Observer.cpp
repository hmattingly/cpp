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
	RwrtOexpE = {
		( _pEarth->getGeoidHeight( gdLat ) + alt ) * std::cos( gdLat ) * std::cos( lon ),
		( _pEarth->getGeoidHeight( gdLat ) + alt ) * std::cos( gdLat ) * std::sin( lon ),
		( _pEarth->getGeoidHeight( gdLat ) * ( 1.0 - Earth::eccentricity * Earth::eccentricity ) + alt ) * std::sin( gdLat )
	};
	Vector3 VwrtEexpD { 
		speed * std::cos( heading ),
		speed * std::sin( heading ),
		0.0
	};
	FrameTransform CfromDtoE;
	CfromDtoE.setD2E( gdLat, lon );
	VwrtEexpE = CfromDtoE.getDCM() * VwrtEexpD;

	// populate initial values
	updateStateDependents();
}

void Observer::initModel()
{
	// NOTE initModel() is executed when Model registered to Integrator

	// register ECI states to be integrated
	registerStates(RwrtOexpE, VwrtEexpE);

	// register outputs with integrator
	registerOutput("RwrtOexpN", RwrtOexpN);
	registerOutput("RwrtOexpE", RwrtOexpE);
	registerOutput("VwrtEexpE", VwrtEexpE);
	registerOutput("VwrtNexpN", VwrtNexpN);

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
	RwrtOexpN = _pEarth->getCfromEtoN() * RwrtOexpE;
	VwrtNexpN = _pEarth->getCfromEtoN() * ( VwrtEexpE + cross( _pEarth->omega, RwrtOexpE ) );
	
	// get longitude, latitude, altitude, and sidereal time
	gcLat = getGeocentricLatitude( RwrtOexpE, RwrtOexpE.mag() );
	gdLat = getGeodeticLatitude( gcLat );
	lon = getLongitude( RwrtOexpE );
	alt = getAltitude( RwrtOexpE, gdLat );
	st = getSiderealTime( RwrtOexpN );

	// set NED tranformation
	CfromNtoD.setN2D( gdLat, st );
	RwrtOexpD = CfromNtoD.getDCM() * RwrtOexpN;
	VwrtNexpD = CfromNtoD.getDCM() * VwrtNexpN;

	// set tropocentric transformation
	CfromNtoT.setN2T( gdLat, st );
	RwrtOexpT = CfromNtoT.getDCM() * RwrtOexpN;
	VwrtNexpT = CfromNtoT.getDCM() * VwrtNexpN;

	Vector3 RwrtSexpD { ZERO_VECTOR3 };

	for ( std::size_t i { 0 }; i < _numSpacecraft; ++i )
	{
		// get range vectors
		RwrtSexpNArray[i] = _pSpacecraftArray[i]->getSpacecraftBody()->RwrtOexpN - RwrtOexpN;
		RwrtSexpEArray[i] = _pSpacecraftArray[i]->getSpacecraftBody()->RwrtOexpE - RwrtOexpE;

		// get right ascension and declination of range vector
		raArray[i] = std::atan2( RwrtSexpNArray[i][1], RwrtSexpNArray[i][0] );
		declArray[i] = std::asin( RwrtSexpNArray[i][2] / RwrtSexpNArray[i].mag() );

		// get azimuth and elevation
		RwrtSexpD = ( CfromNtoD.getDCM() * ( _pSpacecraftArray[i]->getSpacecraftBody()->RwrtOexpN ) ) - RwrtOexpD;
		azArray[i] = std::atan2( RwrtSexpD[1], RwrtSexpD[0] );
		elArray[i] = std::asin( -1.0 * RwrtSexpD[2] / RwrtSexpD.mag() );
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
	registerOutput( getName() + "_to_" + pSpacecraft->getName() + "_RwrtSexpN", RwrtSexpNArray[_numSpacecraft] );
	registerOutput( getName() + "_to_" + pSpacecraft->getName() + "_RwrtSexpE", RwrtSexpEArray[_numSpacecraft] );
	registerOutput( getName() + "_to_" + pSpacecraft->getName() + "_ra", raArray[_numSpacecraft] );
	registerOutput( getName() + "_to_" + pSpacecraft->getName() + "_decl", declArray[_numSpacecraft] );
	registerOutput( getName() + "_to_" + pSpacecraft->getName() + "_az", azArray[_numSpacecraft] );
	registerOutput( getName() + "_to_" + pSpacecraft->getName() + "_el", elArray[_numSpacecraft] );

	// add spacecraft to tracker
	_pSpacecraftArray[_numSpacecraft] = pSpacecraft;
	++_numSpacecraft;
}
