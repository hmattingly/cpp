/*
** ------------ Header Guard -------------
*/ 
#ifndef SPACECRAFTBODY_HH  
#define SPACECRAFTBODY_HH

/*
** ------- Preprocessor directives -------
*/ 
#include "Epoch.hh"
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
	SpacecraftBody();

	// destructor
	~SpacecraftBody() = default;

	// epoch
	Epoch* pEpoch { nullptr };

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
	FrameTransform CfromNtoE;
	Vector3 RwrtOexpE { ZERO_VECTOR3 };
	Vector3 VwrtOexpE { ZERO_VECTOR3 };

	// LVLH / RTN states
	FrameTransform CfromNtoL;
	Vector3 RwrtOexpL { ZERO_VECTOR3 };
	Vector3 VwrtOexpL { ZERO_VECTOR3 };

	// Perifocal states
	FrameTransform CfromNtoP;
	Vector3 RwrtOexpP { ZERO_VECTOR3 };
	Vector3 VwrtOexpP { ZERO_VECTOR3 };

	// specific angular momentum
	Vector3 HwrtOexpN 	 { ZERO_VECTOR3 };	// specific angular momentum
	Vector3 HwrtOexpNhat { ZERO_VECTOR3 };	// specific angular momentum unit vector
	double HwrtOexpNmag  { 0.0 };			// specific angular momentum magnitude

	// line of nodes
	Vector3 NwrtOexpNhat { ZERO_VECTOR3 };	// line of nodes unit vector

	// eccentricity vector
	Vector3 EwrtOexpN    { ZERO_VECTOR3 };	// eccentricity vector

	// Keplerian orbital elements
	double a 	{ 0.0 };  	// semi-major axis
	double b	{ 0.0 };	// semi-minor axis
	double p 	{ 0.0 };	// semi-latus rectum
	double Rp	{ 0.0 };	// periapsis
	double Ra	{ 0.0 };	// apoapsis
	double ecc  { 0.0 };	// eccentricity
	double inc  { 0.0 };	// inclination
	double raan { 0.0 };	// right ascension of the ascending node
	double aop  { 0.0 };	// argument of periapsis
	double aol  { 0.0 };	// argument of latitude
	double ta   { 0.0 };	// true anomaly
	double E    { 0.0 };	// eccentric anomaly
	double M    { 0.0 };	// mean anomaly
	double n	{ 0.0 };	// mean motion
	double P	{ 0.0 };	// orbital period
	double energy { 0.0 };	// specific energy
	double fpa	{ 0.0 };	// flight path angle

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
