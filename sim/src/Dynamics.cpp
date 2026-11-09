/*
** ------- Preprocessor directives -------
*/ 
#include "Dynamics.hh"
#include "Vector.hh"
#include "FrameTransform.hh"
#include "CoordinateTransform.hh"
#include "CelestialBody.hh"
#include "Constants.hh"
#include <cassert>  // for assert()


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
using namespace Constants;

/*
** ----------- Class Definition ------------
*/ 
// constructor
Dynamics::Dynamics(SpacecraftBody* pBody, Earth* pEarth) :
	_pBody { pBody }, _pEarth { pEarth }
{

}

/*
** ----------- Class Definition ------------
*/ 
// constructor
TwoBodyDynamics::TwoBodyDynamics(SpacecraftBody* pBody, Earth* pEarth) :
	Dynamics(pBody, pEarth)
{

}

const Vector3 TwoBodyDynamics::getAwrtNexpN()
{
	return ( -1.0 * Earth::mu / _pBody->RwrtOmag3 * _pBody->RwrtOexpN );
}

/*
** ----------- Class Definition ------------
*/ 
// constructor
J2Dynamics::J2Dynamics(SpacecraftBody* pBody, Earth* pEarth) :
	Dynamics(pBody, pEarth)
{

}

const Vector3 J2Dynamics::getAwrtNexpN()
{
	return ( -1.5 * Earth::mu * Earth::radius * Earth::radius * Earth::J2
			 / _pBody->RwrtOmag5
			 * ( _pBody->RwrtOexpN + 2.0 * _pBody->RwrtOexpN[2] * Z_UNIT_VECTOR3
			 - 5.0 * _pBody->RwrtOexpN[2] * _pBody->RwrtOexpN[2]
			 * _pBody->RwrtOexpN / _pBody->RwrtOmag2 ) );
}

/*
** ----------- Class Definition ------------
*/ 
// constructor
J3Dynamics::J3Dynamics(SpacecraftBody* pBody, Earth* pEarth) :
	Dynamics(pBody, pEarth)
{

}

const Vector3 J3Dynamics::getAwrtNexpN()
{
	Vector3 AwrtNexpE { 
		-1.0 * Earth::mu * Earth::radius * Earth::radius * Earth::radius * Earth::J3
		/ ( 2.0 * _pBody->RwrtOmag7 ) * ( ( 15.0 * _pBody->RwrtOexpE[2] 
		- 35.0 * _pBody->RwrtOexpE[2] * _pBody->RwrtOexpE[2] * _pBody->RwrtOexpE[2] 
		/ _pBody->RwrtOmag2 ) * _pBody->RwrtOexpE + ( 15.0 * _pBody->RwrtOexpE[2] 
		* _pBody->RwrtOexpE[2] - 3.0 * _pBody->RwrtOmag2 ) * Z_UNIT_VECTOR3 )
	};

	return _pEarth->getCfromEtoN() * AwrtNexpE;
	
}

/*
** ----------- Class Definition ------------
*/ 
// constructor
J4Dynamics::J4Dynamics(SpacecraftBody* pBody, Earth* pEarth) :
	Dynamics(pBody, pEarth)
{

}

const Vector3 J4Dynamics::getAwrtNexpN()
{
	Vector3 AwrtNexpE { 
		-5.0 * Earth::mu * Earth::radius * Earth::radius * Earth::radius * Earth::radius
		* Earth::J4 / ( 8.0 * _pBody->RwrtOmag9 ) * ( ( 42.0 * _pBody->RwrtOexpE[2] * _pBody->RwrtOexpE[2]
		- 3.0 * _pBody->RwrtOmag2 - 63.0 * _pBody->RwrtOexpE[2] * _pBody->RwrtOexpE[2]
		* _pBody->RwrtOexpE[2] * _pBody->RwrtOexpE[2] / _pBody->RwrtOmag2 )
		* _pBody->RwrtOexpE + ( 28.0 * _pBody->RwrtOexpE[2] * _pBody->RwrtOexpE[2] * _pBody->RwrtOexpE[2]
		- 12.0 * _pBody->RwrtOexpE[2] * _pBody->RwrtOmag2 ) * Z_UNIT_VECTOR3 )
	};

	return _pEarth->getCfromEtoN() * AwrtNexpE;
	
}

/*
** ----------- Class Definition ------------
*/ 
// constructor
DragDynamics::DragDynamics(SpacecraftBody* pBody, Earth* pEarth) :
	Dynamics(pBody, pEarth)
{

}

const Vector3 DragDynamics::getAwrtNexpN()
{
	_rho = Earth::getDensity( _pBody->alt );

	return (
		-1.0 * 0.5 * _pBody->Cd * _pBody->AMR * _rho * _pBody->VwrtEexpN.mag() * _pBody->VwrtEexpN * KM2M
	);
	
}