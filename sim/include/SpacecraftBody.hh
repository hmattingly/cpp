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

/*
** --------- Namespace directives ---------
*/ 

/*
** ---------- Class Definition -----------
*/ 
class SpacecraftBody
{

public:
	// default constructor (disabled)
	SpacecraftBody() = default;

	// destructor
	~SpacecraftBody() = default;

	// ECI states
	Vector3 RwrtOexpN { ZERO_VECTOR3 };
	Vector3 VwrtOexpN { ZERO_VECTOR3 };
	Vector3 AwrtOexpN { ZERO_VECTOR3 };

	double RwrtOexpNmag  { 0.0 };
	double RwrtOexpNmag2 { 0.0 };
	double RwrtOexpNmag3 { 0.0 };
	double RwrtOexpNmag5 { 0.0 };

	double VwrtOexpNmag  { 0.0 };
	double VwrtOexpNmag2 { 0.0 };

	// ECEF states
	// FrameTransform CfromNtoE;
	// Vector3 RwrtOexpE { ZERO_VECTOR3 };
	// Vector3 VwrtOexpE { ZERO_VECTOR3 };

	// LVLH / RTN states
	FrameTransform CfromNtoL;
	Vector3 RwrtOexpL { ZERO_VECTOR3 };
	Vector3 VwrtOexpL { ZERO_VECTOR3 };

	// Perifocal states
	FrameTransform CfromNtoP;
	Vector3 RwrtOexpP { ZERO_VECTOR3 };
	Vector3 VwrtOexpP { ZERO_VECTOR3 };

	// Keplerian orbital elements
	double a { 0.0 };  					// semi-major axis
	double p { 0.0 };					// semi-latus rectum

	Vector3 h 	 { ZERO_VECTOR3 };		// specific angular momentum
	double hMag  { 0.0 };				// specific angular momentum magnitude
	Vector3 hHat { ZERO_VECTOR3 };		// specific angular momentum unit vector

	Vector3 nHat { ZERO_VECTOR3 };		// line of nodes unit vector

	Vector3 ecc    { ZERO_VECTOR3 };	// eccentricity vector
	double eccMag  { 0.0 };				// eccentricity
	Vector3 eccHat { ZERO_VECTOR3 };	// eccentricity unit vector

	double inc  { 0.0 };				// inclination
	double raan { 0.0 };				// right ascension of the ascending node
	double aop  { 0.0 };				// argument of periapsis
	double aol  { 0.0 };				// argument of latitude
	double ta   { 0.0 };				// true anomaly
	double ea   { 0.0 };				// eccentric anomaly
	double ma   { 0.0 };				// mean anomaly



	// spacecraft physical quantities
	double AMR; // area to mass ratio [m^2/kg]
	double CRd; // diffuse reflectivity [unitless]
	double Cd;	// drag coefficient [unitless]

	// forward declarations
	void updateFromN();

	// setter functions

	// access functions
};

#endif  // SPACECRAFTBODY_HH
