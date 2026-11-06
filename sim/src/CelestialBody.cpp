/*
** ------- Preprocessor directives -------
*/ 
#include "CelestialBody.hh"
#include "Scheduler.hh"
#include "Constants.hh"
#include "Epoch.hh"
#include "Matrix.hh"
#include "FrameTransform.hh"
#include "Model.hh"
#include "InputParser.hh"
#include <cmath>	// for std::fmod()

/*
** -------------- Constants ---------------
*/ 
using namespace Constants;

/*
** -------- Forward Declarations ----------
*/ 

/*
** --------- Namespace directives ---------
*/ 

/*
** ----------- Class Definition ------------
*/ 
Earth::Earth() :
	Model( Earth::name )
{
	// ------- Earth Inputs -------
	const std::string inputFileName { "earth.json" };
	InputParser* pInputFile = new InputParser(inputFileName);

	// grab polar motion values
	setXp(pInputFile->inputFileData["xp"].get<double>());
	setYp(pInputFile->inputFileData["yp"].get<double>());

	// get Epoch pointer
    _pEpoch = Scheduler::getEpoch();

	// free up memory
	delete pInputFile;
}

const double Earth::getDensity(const double& alt)
{
	assert( alt >= 0.0 );

	double h;
	double densityRef;
	double hRef;
	double scaleHeight;
	std::size_t i { 0 };

	do
	{
		h = densityLookup[i][0];
		densityRef = densityLookup[i][1];
		hRef = densityLookup[i][2];
		scaleHeight = densityLookup[i][3];
		++i;
	} while ( alt > h );

	return densityRef * std::exp( ( hRef - alt ) / scaleHeight );
}

const double Earth::getGeoidHeight(const double& geocentricLat)
{
	return radius / std::sqrt( 1.0 - eccentricity * eccentricity * std::sin( geocentricLat ) * std::sin( geocentricLat ) );
}

void Earth::initModel()
{
	// NOTE initModel() is executed when Model registered to Integrator

	// register outputs with integrator
	registerOutput("gmst", _gmst);
	registerOutput("gast", _gast);

	// set initialized flag
	_initialized = true;
}

void Earth::calcPolarMotion()
{
	double cNXp { std::cos( -1.0 * _xp ) };
	double sNXp { std::sin( -1.0 * _xp ) };
	double cNYp { std::cos( -1.0 * _yp ) };
	double sNYp { std::sin( -1.0 * _yp ) };

	Matrix3 Rx {
		{ 1.0, 0.0, 0.0 },
		{ 0.0, cNYp, sNYp },
		{ 0.0, -1.0 * sNYp, cNYp }
	};
	Matrix3 Ry {
		{ cNXp, 0.0, -1.0 * sNXp },
		{ 0.0, 1.0, 0.0 },
		{ sNXp, 0.0, cNXp }
	};

	_PI = Ry * Rx;
}

void Earth::calcNutation()
{
	double t1 { _pEpoch->getT1() };
	double t1_2  { t1 * t1 };
	double t1_3  { t1 * t1_2 };

	// phi coefficients
	double L { 134.0 * DEG2RAD + 57.0 * ARCMIN2RAD + 46.733 * ARCSEC2RAD
			   + ( 477198.0 * DEG2RAD + 52.0 * ARCMIN2RAD + 2.633 * ARCSEC2RAD ) * t1 
			   + 31.31 * ARCSEC2RAD * t1_2
			   + .064 * ARCSEC2RAD * t1_3 };
	double Lp { 357.0 * DEG2RAD + 31.0 * ARCMIN2RAD + 39.804 * ARCSEC2RAD
			 	+ ( 35999.0 * DEG2RAD + 3.0 * ARCMIN2RAD + 1.244 * ARCSEC2RAD ) * t1 
			    - .577 * ARCSEC2RAD * t1_2
			    - .012 * ARCSEC2RAD * t1_3 };
	double F { 93.0 * DEG2RAD + 16.0 * ARCMIN2RAD + 18.877 * ARCSEC2RAD
			   + ( 483202.0 * DEG2RAD + 1.0 * ARCMIN2RAD + 3.137 * ARCSEC2RAD ) * t1 
			   - 13.257 * ARCSEC2RAD * t1_2
			   + .011 * ARCSEC2RAD * t1_3 };
	double D { 297.0 * DEG2RAD + 51.0 * ARCMIN2RAD + 1.307 * ARCSEC2RAD
			   + ( 445267.0 * DEG2RAD + 6.0 * ARCMIN2RAD + 41.328 * ARCSEC2RAD ) * t1 
			   - 6.891 * ARCSEC2RAD * t1_2
			   + .019 * ARCSEC2RAD * t1_3 };
	double O { 125.0 * DEG2RAD + 2.0 * ARCMIN2RAD + 40.28 * ARCSEC2RAD
			   - ( 1934.0 * DEG2RAD + 8.0 * ARCMIN2RAD + 10.539 * ARCSEC2RAD ) * t1 
			   + 7.455 * ARCSEC2RAD * t1_2
			   + .008 * ARCSEC2RAD * t1_3 };

	// dPsi and dEpsilon coefficients
	double a;
	double b;
	double c;
	double d;
	double phi;
	double dPsi { 0.0 };
	double dEpsilon { 0.0 };

	for ( std::size_t i { 0 }; i < EarthOrientation::NUTATION_ROW_COUNT; ++i )
	{
		phi = nutationCoeff[i][0] * L 
			  + nutationCoeff[i][1] * Lp 
			  + nutationCoeff[i][2] * F 
			  + nutationCoeff[i][3] * D 
			  + nutationCoeff[i][4] * O;
		a = 0.0001 * nutationCoeff[i][5] * ARCSEC2RAD;
		b = 0.0001 * nutationCoeff[i][6] * ARCSEC2RAD;
		c = 0.0001 * nutationCoeff[i][7] * ARCSEC2RAD;
		d = 0.0001 * nutationCoeff[i][8] * ARCSEC2RAD;
		
		dPsi += ( a + b * t1 ) * std::sin( phi );
		dEpsilon += ( c + d * t1 ) * std::cos( phi );
	}

	// update nutation of longitude
	_dPsi = dPsi;

	// update mean obliquity of the ecliptic
	_meanEpsilon = ARCSEC2RAD * ( 84381.448 - 46.8150 * t1 - 0.00059 * t1_2 + 0.001813 * t1_3 );

	// update true obliquity of the ecliptic
	_trueEpsilon = _meanEpsilon + dEpsilon;

	// update nutation matrix
	FrameTransform nutationTransform;
	nutationTransform.setEulerAngles131( _meanEpsilon, -1.0 * dPsi, -1.0 * _trueEpsilon );
	_NU = nutationTransform.getDCM();
}

void Earth::calcPrecession()
{
	double t1 { _pEpoch->getT1() };
	double t1_2  { t1 * t1 };
	double t1_3  { t1 * t1_2 };

	double zeta  { ARCSEC2RAD * ( 2306.2181 * t1 + .30188 * t1_2 + .017998 * t1_3 ) };
	double theta { ARCSEC2RAD * ( 2004.3109 * t1 - .42665 * t1_2 - .041833 * t1_3 ) };
	double z 	 { zeta + ARCSEC2RAD * ( .79280 * t1_2 + .000205 * t1_3 ) };

	FrameTransform precessionTransform;
	precessionTransform.setEulerAngles323( -1.0 * zeta, theta, -1.0 * z );
	_PR = precessionTransform.getDCM();
}

void Earth::calcEarthRotation()
{
	double t0 { _pEpoch->getT0() };
	double t0_2 { t0 * t0 };
	double t0_3 { t0 * t0_2 };
	double utc { _pEpoch->getUTC() };

	// update GMST
	double gmstSec { 24'110.54841 + 8'640'184.812866 * t0 
					 + 0.093104 * t0_2
					 - 0.0000062 * t0_3
					 + 1.002737909350795 * ( utc * 3600.0 ) };

	  // convert from sec to rad
	_gmst = std::fmod( gmstSec / 240.0, 360.0 ) * DEG2RAD;
	if ( _gmst < 0.0 )
	{
		_gmst += TWO_PI;
	}

	// update GAST
	_gast = _gmst + _dPsi * std::cos( _meanEpsilon );

	// update Earth rotation matrix
	_TH = FrameTransform::getRot3( _gast );
}

void Earth::updateDerivs()
{
	// no derivatives to update
}

void Earth::updateStateDependents()
{
	// update polar motion matrix
	calcPolarMotion();

	// update nutation matrix
	calcNutation();

	// update precession matrix
	calcPrecession();

	// update Earth rotation matrix (must be called after calcNutation)
	calcEarthRotation();
}

