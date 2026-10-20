/*
** ------------ Header Guard -------------
*/ 
#ifndef SPACECRAFTBODY_HH  
#define SPACECRAFTBODY_HH

/*
** ------- Preprocessor directives -------
*/ 
#include "Vector.hh"

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
** ---------- Struct Definition -----------
*/ 
struct SpacecraftBody
{
	// ECI states
	Vector3 RwrtOexpN { ZERO_VECTOR3 };
	Vector3 VwrtOexpN { ZERO_VECTOR3 };
	Vector3 AwrtOexpN { ZERO_VECTOR3 };

	double RwrtOexpNmag { 0.0 };
	double RwrtOexpNmag2 { 0.0 };
	double RwrtOexpNmag3 { 0.0 };
	double RwrtOexpNmag5 { 0.0 };

	double VwrtOexpNmag { 0.0 };
	double VwrtOexpNmag2 { 0.0 };
	double AwrtOexpNmag { 0.0 };

	// ECEF states
	Vector3 RwrtOexpE { ZERO_VECTOR3 };
	Vector3 VwrtOexpE { ZERO_VECTOR3 };

	// spacecraft physical quantities
	double AMR; // area to mass ratio [m^2/kg]
	double CRd; // diffuse reflectivity [unitless]
	double Cd;	// drag coefficient [unitless]
};

#endif  // SPACECRAFTBODY_HH
