/*
** ------- Preprocessor directives -------
*/ 
#include "Dynamics.hh"
#include "Vector.hh"
#include "FrameTransform.hh"
#include "CelestialBody.hh"


/*
** -------------- Constants ---------------
*/ 

/*
** -------- Forward Declarations ----------
*/ 

/*
** --------- Namespace directives ---------
*/ 
using namespace CelestialBodies;

/*
** ----------- Class Definition ------------
*/ 
// constructor
Dynamics::Dynamics(SpacecraftBody* body) :
	_body { body }
{

}

/*
** ----------- Class Definition ------------
*/ 
// constructor
TwoBodyDynamics::TwoBodyDynamics(SpacecraftBody* body) :
	Dynamics(body)
{

}

const Vector3 TwoBodyDynamics::getAwrtOexpN()
{
	return ( -1.0 * EARTH.mu / _body->RwrtOmag3 * _body->RwrtOexpN );
}

/*
** ----------- Class Definition ------------
*/ 
// constructor
J2Dynamics::J2Dynamics(SpacecraftBody* body) :
	Dynamics(body),
	_J2 { EARTH.J2.value() }
{

}

const Vector3 J2Dynamics::getAwrtOexpN()
{
	return ( -1.5 * EARTH.mu * EARTH.radius * EARTH.radius * _J2
			 / _body->RwrtOmag5
			 * ( _body->RwrtOexpN + 2.0 * _body->RwrtOexpN[2] * Z_UNIT_VECTOR3
			 - 5.0 * _body->RwrtOexpN[2] * _body->RwrtOexpN[2]
			 * _body->RwrtOexpN / _body->RwrtOmag2 ) );
}

/*
** ----------- Class Definition ------------
*/ 
// constructor
J3Dynamics::J3Dynamics(SpacecraftBody* body) :
	Dynamics(body),
	_J3 { EARTH.J3.value() }
{

}

const Vector3 J3Dynamics::getAwrtOexpN()
{
	Matrix3 CfromEtoN { _body->CfromNtoE.getDCM().transpose() };
	Vector3 AwrtOexpE { 
		-1.0 * EARTH.mu * EARTH.radius * EARTH.radius * EARTH.radius * _J3
		/ ( 2.0 * _body->RwrtOmag7 ) * ( ( 15.0 * _body->RwrtOexpE[2] 
		- 35.0 * _body->RwrtOexpE[2] * _body->RwrtOexpE[2] * _body->RwrtOexpE[2] 
		/ _body->RwrtOmag2 ) * _body->RwrtOexpE + ( 15.0 * _body->RwrtOexpE[2] 
		* _body->RwrtOexpE[2] - 3.0 * _body->RwrtOmag2 ) * Z_UNIT_VECTOR3 )
	};

	return CfromEtoN * AwrtOexpE;
	
}

/*
** ----------- Class Definition ------------
*/ 
// constructor
J4Dynamics::J4Dynamics(SpacecraftBody* body) :
	Dynamics(body),
	_J4 { EARTH.J4.value() }
{

}

const Vector3 J4Dynamics::getAwrtOexpN()
{
	Matrix3 CfromEtoN { _body->CfromNtoE.getDCM().transpose() };
	Vector3 AwrtOexpE { 
		-5.0 * EARTH.mu * EARTH.radius * EARTH.radius * EARTH.radius * EARTH.radius
		* _J4 / ( 8.0 * _body->RwrtOmag9 ) * ( ( 42.0 * _body->RwrtOexpE[2] * _body->RwrtOexpE[2]
		- 3.0 * _body->RwrtOmag2 - 63.0 * _body->RwrtOexpE[2] * _body->RwrtOexpE[2]
		* _body->RwrtOexpE[2] * _body->RwrtOexpE[2] / _body->RwrtOmag2 )
		* _body->RwrtOexpE + ( 28.0 * _body->RwrtOexpE[2] * _body->RwrtOexpE[2] * _body->RwrtOexpE[2]
		- 12.0 * _body->RwrtOexpE[2] * _body->RwrtOmag2 ) * Z_UNIT_VECTOR3 )
	};

	return CfromEtoN * AwrtOexpE;
	
}
