/*
** ------- Preprocessor directives -------
*/ 
#include "SpacecraftBody.hh"
#include "FrameTransform.hh"
#include "CoordinateTransform.hh"

/*
** -------------- Constants ---------------
*/ 

/*
** -------- Forward Declarations ----------
*/ 

/*
** --------- Namespace directives ---------
*/ 
using namespace CoordinateTransform;

/*
** ----------- Class Definition ------------
*/ 

void SpacecraftBody::updateFromN()
{
	// update position magnitudes
	RwrtOexpNmag = RwrtOexpN.mag();
	assert(RwrtOexpNmag > 0.0);
	RwrtOexpNmag2 = RwrtOexpNmag * RwrtOexpNmag;
	RwrtOexpNmag3 = RwrtOexpNmag2 * RwrtOexpNmag;
	RwrtOexpNmag5 = RwrtOexpNmag3 * RwrtOexpNmag2;

	// update velocity magnitudes
	VwrtOexpNmag = VwrtOexpN.mag();
	VwrtOexpNmag2 = VwrtOexpNmag * VwrtOexpNmag;

	// convert inertial state to keplerian orbital elements
	kepOE = N2kepoe( RwrtOexpN, VwrtOexpN );

	// convert from ECI to LVLH
	CfromNtoL.setN2L( kepOE[2], kepOE[3], kepOE[4] + kepOE[5] );
	RwrtOexpL = CfromNtoL.getDCM() * RwrtOexpN;
	VwrtOexpL = CfromNtoL.getDCM() * VwrtOexpN;

	// convert from ECI to Perifocal
	CfromNtoP.setN2P( kepOE[2], kepOE[3], kepOE[4] );
	RwrtOexpP = CfromNtoP.getDCM() * RwrtOexpN;
	VwrtOexpP = CfromNtoP.getDCM() * VwrtOexpN;
}
