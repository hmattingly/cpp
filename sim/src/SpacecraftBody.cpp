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

void SpacecraftBody::updateFromN(const bool& atSolPoint=true)
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

	// optional parameters only need to be updated at solution point
	if ( true == atSolPoint )
	{
		// specific angular momentum
		HwrtOexpN = getSpecAngularMomentum( RwrtOexpN, VwrtOexpN );
		HwrtOexpNmag = HwrtOexpN.mag();
		assert(HwrtOexpNmag > 0.0);
		HwrtOexpNhat = HwrtOexpN / HwrtOexpNmag;

		// line of nodes
		NwrtOexpNhat = getLineOfNodesUnit( HwrtOexpN );

		// convert inertial state to keplerian orbital elements
		Vector6 kepOE = N2kepoe( RwrtOexpN, VwrtOexpN );
		a 		= kepOE[0];
		ecc 	= kepOE[1];
		inc 	= kepOE[2];
		raan 	= kepOE[3];
		aop 	= kepOE[4];
		ta 		= kepOE[5];

		b 			= getSemiminorAxis( a, ecc );
		p 			= getSemilatusRectum( HwrtOexpNmag );
		Ra 			= getApoapsis( p, ecc );
		Rp 			= getPeriapsis( p, ecc );
		n 			= getMeanMotion( a );
		P			= getPeriod( n );
		energy 		= getSpecEnergy( a );
		EwrtOexpN	= getEccentricityVector( RwrtOexpN, VwrtOexpN );
		aol 		= aop + ta;
		E 			= getEccentricAnomaly( ecc, ta );
		M 			= getMeanAnomaly( ecc, E );
		fpa 		= getFlightPathAngle( RwrtOexpN, VwrtOexpN );

		// convert from ECI to LVLH
		CfromNtoL.setN2L( inc, raan, aol );
		RwrtOexpL = CfromNtoL.getDCM() * RwrtOexpN;
		VwrtOexpL = CfromNtoL.getDCM() * VwrtOexpN;

		// convert from ECI to Perifocal
		CfromNtoP.setN2P( inc, raan, aop );
		RwrtOexpP = CfromNtoP.getDCM() * RwrtOexpN;
		VwrtOexpP = CfromNtoP.getDCM() * VwrtOexpN;
	}
}

void SpacecraftBody::updateFromKepOE(const bool& atSolPoint=true)
{
	// convert keplerian orbital elements to inertial state
	Vector6 stateN { kepoe2N( a, ecc, inc, raan, aop, ta ) };
	RwrtOexpN = { stateN[0], stateN[1], stateN[2] };
	VwrtOexpN = { stateN[3], stateN[4], stateN[5] };

	// update position magnitudes
	RwrtOexpNmag = RwrtOexpN.mag();
	assert(RwrtOexpNmag > 0.0);
	RwrtOexpNmag2 = RwrtOexpNmag * RwrtOexpNmag;
	RwrtOexpNmag3 = RwrtOexpNmag2 * RwrtOexpNmag;
	RwrtOexpNmag5 = RwrtOexpNmag3 * RwrtOexpNmag2;

	// update velocity magnitudes
	VwrtOexpNmag = VwrtOexpN.mag();
	VwrtOexpNmag2 = VwrtOexpNmag * VwrtOexpNmag;

	// optional parameters only need to be updated at solution point
	if ( true == atSolPoint )
	{
		// specific angular momentum
		HwrtOexpN = getSpecAngularMomentum( RwrtOexpN, VwrtOexpN );
		HwrtOexpNmag = HwrtOexpN.mag();
		assert(HwrtOexpNmag > 0.0);
		HwrtOexpNhat = HwrtOexpN / HwrtOexpNmag;

		// line of nodes
		NwrtOexpNhat = getLineOfNodesUnit( HwrtOexpN );

		// get optional parameters
		b 			= getSemiminorAxis( a, ecc );
		p 			= getSemilatusRectum( HwrtOexpNmag );
		Ra 			= getApoapsis( p, ecc );
		Rp 			= getPeriapsis( p, ecc );
		n 			= getMeanMotion( a );
		P			= getPeriod( n );
		energy 		= getSpecEnergy( a );
		EwrtOexpN	= getEccentricityVector( RwrtOexpN, VwrtOexpN );
		aol 		= aop + ta;
		E 			= getEccentricAnomaly( ecc, ta );
		M 			= getMeanAnomaly( ecc, E );
		fpa 		= getFlightPathAngle( RwrtOexpN, VwrtOexpN );

		// convert from ECI to LVLH
		CfromNtoL.setN2L( inc, raan, aol );
		RwrtOexpL = CfromNtoL.getDCM() * RwrtOexpN;
		VwrtOexpL = CfromNtoL.getDCM() * VwrtOexpN;

		// convert from ECI to Perifocal
		CfromNtoP.setN2P( inc, raan, aop );
		RwrtOexpP = CfromNtoP.getDCM() * RwrtOexpN;
		VwrtOexpP = CfromNtoP.getDCM() * VwrtOexpN;
	}
}
