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

SpacecraftBody::SpacecraftBody(Earth* pEarth) : 
	_pEarth { pEarth }
{

}

void SpacecraftBody::updateFromI(const bool& atSolPoint=true)
{
	// update position magnitudes
	RofBwrtCmag = RofBwrtCexpI.mag();
	assert(RofBwrtCmag > 0.0);
	RofBwrtCmag2 = RofBwrtCmag * RofBwrtCmag;
	RofBwrtCmag3 = RofBwrtCmag2 * RofBwrtCmag;
	RofBwrtCmag5 = RofBwrtCmag3 * RofBwrtCmag2;
	RofBwrtCmag7 = RofBwrtCmag5 * RofBwrtCmag2;
	RofBwrtCmag9 = RofBwrtCmag7 * RofBwrtCmag2;

	// update velocity magnitudes
	VofBwrtImag = VofBwrtIexpI.mag();
	VofBwrtImag2 = VofBwrtImag * VofBwrtImag;

	// convert from ECI to ECEF
	RofBwrtCexpE = _pEarth->getCfromItoE() * RofBwrtCexpI;
	VofBwrtIexpE = _pEarth->getCfromItoE() * VofBwrtIexpI;
	VofBwrtEexpE = VofBwrtIexpE - cross( _pEarth->WofEwrtIexpE, RofBwrtCexpE );
	VofBwrtEexpI = VofBwrtIexpI - cross( _pEarth->getCfromEtoI() * _pEarth->WofEwrtIexpE, RofBwrtCexpI );

	// optional parameters only need to be updated at solution point
	if ( true == atSolPoint )
	{
		// specific angular momentum
		HofBwrtCexpI = getSpecAngularMomentum( RofBwrtCexpI, VofBwrtIexpI );
		HofBwrtCmag = HofBwrtCexpI.mag();
		assert(HofBwrtCmag > 0.0);
		HofBwrtCexpIhat = HofBwrtCexpI / HofBwrtCmag;

		// line of nodes
		NofBwrtCexpIhat = getLineOfNodesUnit( HofBwrtCexpI );

		// convert inertial state to keplerian orbital elements
		Vector6 kepOE = I2kepoe( RofBwrtCexpI, VofBwrtIexpI );
		a 		= kepOE[0];
		ecc 	= kepOE[1];
		inc 	= kepOE[2];
		raan 	= kepOE[3];
		aop 	= kepOE[4];
		ta 		= kepOE[5];

		b 			= getSemiminorAxis( a, ecc );
		p 			= getSemilatusRectum( HofBwrtCmag );
		Ra 			= getApoapsis( p, ecc );
		Rp 			= getPeriapsis( p, ecc );
		n 			= getMeanMotion( a );
		P			= getPeriod( n );
		energy 		= getSpecEnergy( a );
		EofBwrtCexpI	= getEccentricityVector( RofBwrtCexpI, VofBwrtIexpI );
		aol 		= aop + ta;
		E 			= getEccentricAnomaly( ecc, ta );
		M 			= getMeanAnomaly( ecc, E );
		fpa 		= getFlightPathAngle( RofBwrtCexpI, VofBwrtIexpI );

		gcLat		= getGeocentricLatitude( RofBwrtCexpE, RofBwrtCmag );
		gdLat		= getGeodeticLatitude( gcLat );
		lon			= getLongitude( RofBwrtCexpE );
		alt			= getAltitude( RofBwrtCexpE, gdLat );
		gcRA		= getRightAscension( RofBwrtCexpI );
		gcDecl		= gcLat;
		gmha		= _pEarth->getGMST() - gcRA;

		// convert from ECI to LVLH
		CfromItoL.setI2L( inc, raan, aol );
		RofBwrtCexpL = CfromItoL.getDCM() * RofBwrtCexpI;
		VofBwrtIexpL = CfromItoL.getDCM() * VofBwrtIexpI;

		// convert from ECI to Perifocal
		CfromItoP.setI2P( inc, raan, aop );
		RofBwrtCexpP = CfromItoP.getDCM() * RofBwrtCexpI;
		VofBwrtIexpP = CfromItoP.getDCM() * VofBwrtIexpI;
	}
}

void SpacecraftBody::updateFromKepOE(const bool& atSolPoint=true)
{
	// convert keplerian orbital elements to inertial state
	Vector6 stateI { kepoe2I( a, ecc, inc, raan, aop, ta ) };
	RofBwrtCexpI = { stateI[0], stateI[1], stateI[2] };
	VofBwrtIexpI = { stateI[3], stateI[4], stateI[5] };

	// update position magnitudes
	RofBwrtCmag = RofBwrtCexpI.mag();
	assert(RofBwrtCmag > 0.0);
	RofBwrtCmag2 = RofBwrtCmag * RofBwrtCmag;
	RofBwrtCmag3 = RofBwrtCmag2 * RofBwrtCmag;
	RofBwrtCmag5 = RofBwrtCmag3 * RofBwrtCmag2;
	RofBwrtCmag7 = RofBwrtCmag5 * RofBwrtCmag2;
	RofBwrtCmag9 = RofBwrtCmag7 * RofBwrtCmag2;

	// update velocity magnitudes
	VofBwrtImag = VofBwrtIexpI.mag();
	VofBwrtImag2 = VofBwrtImag * VofBwrtImag;

	// convert from ECI to ECEF
	RofBwrtCexpE = _pEarth->getCfromItoE() * RofBwrtCexpI;
	VofBwrtIexpE = _pEarth->getCfromItoE() * VofBwrtIexpI;
	VofBwrtEexpE = VofBwrtIexpE - cross( _pEarth->WofEwrtIexpE, RofBwrtCexpE );
	VofBwrtEexpI = VofBwrtIexpI - cross( _pEarth->getCfromEtoI() * _pEarth->WofEwrtIexpE, RofBwrtCexpI );

	// optional parameters only need to be updated at solution point
	if ( true == atSolPoint )
	{
		// specific angular momentum
		HofBwrtCexpI = getSpecAngularMomentum( RofBwrtCexpI, VofBwrtIexpI );
		HofBwrtCmag = HofBwrtCexpI.mag();
		assert(HofBwrtCmag > 0.0);
		HofBwrtCexpIhat = HofBwrtCexpI / HofBwrtCmag;

		// line of nodes
		NofBwrtCexpIhat = getLineOfNodesUnit( HofBwrtCexpI );

		// get optional parameters
		b 			= getSemiminorAxis( a, ecc );
		p 			= getSemilatusRectum( HofBwrtCmag );
		Ra 			= getApoapsis( p, ecc );
		Rp 			= getPeriapsis( p, ecc );
		n 			= getMeanMotion( a );
		P			= getPeriod( n );
		energy 		= getSpecEnergy( a );
		EofBwrtCexpI	= getEccentricityVector( RofBwrtCexpI, VofBwrtIexpI );
		aol 		= aop + ta;
		E 			= getEccentricAnomaly( ecc, ta );
		M 			= getMeanAnomaly( ecc, E );
		fpa 		= getFlightPathAngle( RofBwrtCexpI, VofBwrtIexpI );

		gcLat		= getGeocentricLatitude( RofBwrtCexpE, RofBwrtCmag );
		gdLat		= getGeodeticLatitude( gcLat );
		lon			= getLongitude( RofBwrtCexpE );
		alt			= getAltitude( RofBwrtCexpE, gdLat );
		gcRA		= getRightAscension( RofBwrtCexpI );
		gcDecl		= gcLat;
		gmha		= _pEarth->getGMST() - gcRA;

		// convert from ECI to LVLH
		CfromItoL.setI2L( inc, raan, aol );
		RofBwrtCexpL = CfromItoL.getDCM() * RofBwrtCexpI;
		VofBwrtIexpL = CfromItoL.getDCM() * VofBwrtIexpI;

		// convert from ECI to Perifocal
		CfromItoP.setI2P( inc, raan, aop );
		RofBwrtCexpP = CfromItoP.getDCM() * RofBwrtCexpI;
		VofBwrtIexpP = CfromItoP.getDCM() * VofBwrtIexpI;
	}
}
