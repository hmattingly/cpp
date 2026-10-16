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
	Vector3 RwrtOexpN { 0.0, 0.0, 0.0  };
	Vector3 VwrtOexpN { 0.0, 0.0, 0.0  };
	Vector3 AwrtOexpN { 0.0, 0.0, 0.0  };
	double AMR; // area to mass ratio [m^2/kg]
	double CRd; // diffuse reflectivity [unitless]
	double Cd;	// drag coefficient [unitless]
};

#endif  // SPACECRAFTBODY_HH
