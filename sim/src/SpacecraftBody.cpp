/*
** ------- Preprocessor directives -------
*/
#include "Scheduler.hh" 
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

// reference definitions
  // O = Center of Earth
  // B = Center of Mass of Body
// frame definitions
  // N = ECI
  // E = ECEF
  // P = Perifocal
  // L = LVLH / RTN

SpacecraftBody::SpacecraftBody(Earth* pEarth) : 
	_pEarth { pEarth }
{

}

void SpacecraftBody::updateFromN(const bool& atSolPoint=true)
{
	// update position magnitudes
	RwrtOmag = RwrtOexpN.mag();
	assert(RwrtOmag > 0.0);
	RwrtOmag2 = RwrtOmag * RwrtOmag;
	RwrtOmag3 = RwrtOmag2 * RwrtOmag;
	RwrtOmag5 = RwrtOmag3 * RwrtOmag2;
	RwrtOmag7 = RwrtOmag5 * RwrtOmag2;
	RwrtOmag9 = RwrtOmag7 * RwrtOmag2;

	// update velocity magnitudes
	VwrtNmag = VwrtNexpN.mag();
	VwrtNmag2 = VwrtNmag * VwrtNmag;

	// convert from ECI to ECEF
	CfromNtoE.setN2E( _pEarth );
	RwrtOexpE = CfromNtoE.getDCM() * RwrtOexpN;
	VwrtNexpE = CfromNtoE.getDCM() * VwrtNexpN;
	VwrtEexpE = CfromNtoE.getDCM() * VwrtNexpN - cross( _pEarth->omega, RwrtOexpE );

	// optional parameters only need to be updated at solution point
	if ( true == atSolPoint )
	{
		// specific angular momentum
		HwrtOexpN = getSpecAngularMomentum( RwrtOexpN, VwrtNexpN );
		HwrtOmag = HwrtOexpN.mag();
		assert(HwrtOmag > 0.0);
		HwrtOexpNhat = HwrtOexpN / HwrtOmag;

		// line of nodes
		NwrtOexpNhat = getLineOfNodesUnit( HwrtOexpN );

		// convert inertial state to keplerian orbital elements
		Vector6 kepOE = N2kepoe( RwrtOexpN, VwrtNexpN );
		a 		= kepOE[0];
		ecc 	= kepOE[1];
		inc 	= kepOE[2];
		raan 	= kepOE[3];
		aop 	= kepOE[4];
		ta 		= kepOE[5];

		b 			= getSemiminorAxis( a, ecc );
		p 			= getSemilatusRectum( HwrtOmag );
		Ra 			= getApoapsis( p, ecc );
		Rp 			= getPeriapsis( p, ecc );
		n 			= getMeanMotion( a );
		P			= getPeriod( n );
		energy 		= getSpecEnergy( a );
		EwrtOexpN	= getEccentricityVector( RwrtOexpN, VwrtNexpN );
		aol 		= aop + ta;
		E 			= getEccentricAnomaly( ecc, ta );
		M 			= getMeanAnomaly( ecc, E );
		fpa 		= getFlightPathAngle( RwrtOexpN, VwrtNexpN );

		// convert from ECI to LVLH
		CfromNtoL.setN2L( inc, raan, aol );
		RwrtOexpL = CfromNtoL.getDCM() * RwrtOexpN;
		VwrtNexpL = CfromNtoL.getDCM() * VwrtNexpN;

		// convert from ECI to Perifocal
		CfromNtoP.setN2P( inc, raan, aop );
		RwrtOexpP = CfromNtoP.getDCM() * RwrtOexpN;
		VwrtNexpP = CfromNtoP.getDCM() * VwrtNexpN;
	}
}

void SpacecraftBody::updateFromKepOE(const bool& atSolPoint=true)
{
	// convert keplerian orbital elements to inertial state
	Vector6 stateN { kepoe2N( a, ecc, inc, raan, aop, ta ) };
	RwrtOexpN = { stateN[0], stateN[1], stateN[2] };
	VwrtNexpN = { stateN[3], stateN[4], stateN[5] };

	// update position magnitudes
	RwrtOmag = RwrtOexpN.mag();
	assert(RwrtOmag > 0.0);
	RwrtOmag2 = RwrtOmag * RwrtOmag;
	RwrtOmag3 = RwrtOmag2 * RwrtOmag;
	RwrtOmag5 = RwrtOmag3 * RwrtOmag2;
	RwrtOmag7 = RwrtOmag5 * RwrtOmag2;
	RwrtOmag9 = RwrtOmag7 * RwrtOmag2;

	// update velocity magnitudes
	VwrtNmag = VwrtNexpN.mag();
	VwrtNmag2 = VwrtNmag * VwrtNmag;

	// convert from ECI to ECEF
	CfromNtoE.setN2E( _pEarth );
	RwrtOexpE = CfromNtoE.getDCM() * RwrtOexpN;
	VwrtNexpE = CfromNtoE.getDCM() * VwrtNexpN;
	VwrtEexpE = VwrtNexpE - cross( _pEarth->omega, RwrtOexpE );

	// optional parameters only need to be updated at solution point
	if ( true == atSolPoint )
	{
		// specific angular momentum
		HwrtOexpN = getSpecAngularMomentum( RwrtOexpN, VwrtNexpN );
		HwrtOmag = HwrtOexpN.mag();
		assert(HwrtOmag > 0.0);
		HwrtOexpNhat = HwrtOexpN / HwrtOmag;

		// line of nodes
		NwrtOexpNhat = getLineOfNodesUnit( HwrtOexpN );

		// get optional parameters
		b 			= getSemiminorAxis( a, ecc );
		p 			= getSemilatusRectum( HwrtOmag );
		Ra 			= getApoapsis( p, ecc );
		Rp 			= getPeriapsis( p, ecc );
		n 			= getMeanMotion( a );
		P			= getPeriod( n );
		energy 		= getSpecEnergy( a );
		EwrtOexpN	= getEccentricityVector( RwrtOexpN, VwrtNexpN );
		aol 		= aop + ta;
		E 			= getEccentricAnomaly( ecc, ta );
		M 			= getMeanAnomaly( ecc, E );
		fpa 		= getFlightPathAngle( RwrtOexpN, VwrtNexpN );

		// convert from ECI to LVLH
		CfromNtoL.setN2L( inc, raan, aol );
		RwrtOexpL = CfromNtoL.getDCM() * RwrtOexpN;
		VwrtNexpL = CfromNtoL.getDCM() * VwrtNexpN;

		// convert from ECI to Perifocal
		CfromNtoP.setN2P( inc, raan, aop );
		RwrtOexpP = CfromNtoP.getDCM() * RwrtOexpN;
		VwrtNexpP = CfromNtoP.getDCM() * VwrtNexpN;
	}
}
