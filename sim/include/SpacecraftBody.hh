/*
** ------------ Header Guard -------------
*/ 
#ifndef SPACECRAFTBODY_HH  
#define SPACECRAFTBODY_HH

/*
** ------- Preprocessor directives -------
*/ 
#include "Vector.hh"
#include "FrameTransform.hh"

/*
** -------------- Constants ---------------
*/ 

/*
** -------- Forward Declarations ----------
*/ 
class Earth;

/*
** --------- Namespace directives ---------
*/ 

/*
** ---------- Class Definition -----------
*/ 

// reference definitions
  // O = Center of Earth
  // B = Center of Mass of Body
// frame definitions
  // N = ECI
  // E = ECEF
  // P = Perifocal
  // L = LVLH / RTN

class SpacecraftBody
{
	Earth* _pEarth { nullptr };

public:
	// default constructor
	SpacecraftBody(Earth* pEarth);

	// destructor
	~SpacecraftBody() = default;

	// ECI states
	Vector3 RwrtOexpN { ZERO_VECTOR3 };
	Vector3 VwrtNexpN { ZERO_VECTOR3 };
	Vector3 AwrtNexpN { ZERO_VECTOR3 };

	double RwrtOmag  { 0.0 };
	double RwrtOmag2 { 0.0 };
	double RwrtOmag3 { 0.0 };
	double RwrtOmag5 { 0.0 };
	double RwrtOmag7 { 0.0 };
	double RwrtOmag9 { 0.0 };

	double VwrtNmag  { 0.0 };
	double VwrtNmag2 { 0.0 };

	// ECEF states
	Vector3 RwrtOexpE { ZERO_VECTOR3 };
	Vector3 VwrtNexpE { ZERO_VECTOR3 };
	Vector3 VwrtEexpE { ZERO_VECTOR3 };
	Vector3 VwrtEexpN { ZERO_VECTOR3 };

	// LVLH / RTN states
	FrameTransform CfromNtoL;
	Vector3 RwrtOexpL { ZERO_VECTOR3 };
	Vector3 VwrtNexpL { ZERO_VECTOR3 };

	// Perifocal states
	FrameTransform CfromNtoP;
	Vector3 RwrtOexpP { ZERO_VECTOR3 };
	Vector3 VwrtNexpP { ZERO_VECTOR3 };

	// specific angular momentum
	Vector3 HwrtOexpN 	 { ZERO_VECTOR3 };	// specific angular momentum
	Vector3 HwrtOexpNhat { ZERO_VECTOR3 };	// specific angular momentum unit vector
	double HwrtOmag  { 0.0 };				// specific angular momentum magnitude

	// line of nodes
	Vector3 NwrtOexpNhat { ZERO_VECTOR3 };	// line of nodes unit vector

	// eccentricity vector
	Vector3 EwrtOexpN    { ZERO_VECTOR3 };	// eccentricity vector

	// Keplerian orbital elements
	double a 	{ 0.0 };  	// semi-major axis [km]
	double b	{ 0.0 };	// semi-minor axis [km]
	double p 	{ 0.0 };	// semi-latus rectum [km]
	double Rp	{ 0.0 };	// periapsis [km]
	double Ra	{ 0.0 };	// apoapsis [km]
	double ecc  { 0.0 };	// eccentricity [unitless]
	double inc  { 0.0 };	// inclination [rad]
	double raan { 0.0 };	// right ascension of the ascending node [rad]
	double aop  { 0.0 };	// argument of periapsis [rad]
	double aol  { 0.0 };	// argument of latitude [rad]
	double ta   { 0.0 };	// true anomaly [rad]
	double E    { 0.0 };	// eccentric anomaly [rad]
	double M    { 0.0 };	// mean anomaly [rad]
	double n	{ 0.0 };	// mean motion [rad/s]
	double P	{ 0.0 };	// orbital period [s]
	double energy { 0.0 };	// specific energy [km^2/s^2]
	double fpa	{ 0.0 };	// flight path angle [rad]

	// latitude, longitude, altitude
	double gcLat  	{ 0.0 };	// geocentric latitude [rad]
	double gdLat    { 0.0 };  	// geodetic latitude [rad]
	double lon		{ 0.0 };	// longitude [rad]
	double alt 		{ 0.0 };	// altitude above geoid [km]
	double gcRA   	{ 0.0 };	// geocentric right ascension [rad]
	double gcDecl 	{ 0.0 };	// geocentric declination [rad]
	double gmha		{ 0.0 };	// Greenwich mean hour angle [rad]

	// spacecraft physical quantities
	double AMR;	// area to mass ratio [m^2/kg]
	double CRd; // diffuse reflectivity [unitless]
	double Cd;	// drag coefficient [unitless]

	// forward declarations
	void updateFromN(const bool& atSolPoint);
	void updateFromKepOE(const bool& atSolPoint);

	// setter functions

	// access functions
};

#endif  // SPACECRAFTBODY_HH
