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

const Vector3 TwoBodyDynamics::getAwrtNexpN()
{
	return ( -1.0 * Earth::mu / _body->RwrtOmag3 * _body->RwrtOexpN );
}

/*
** ----------- Class Definition ------------
*/ 
// constructor
J2Dynamics::J2Dynamics(SpacecraftBody* body) :
	Dynamics(body)
{

}

const Vector3 J2Dynamics::getAwrtNexpN()
{
	return ( -1.5 * Earth::mu * Earth::radius * Earth::radius * Earth::J2
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
	Dynamics(body)
{

}

const Vector3 J3Dynamics::getAwrtNexpN()
{
	Matrix3 CfromEtoN { _body->CfromNtoE.getDCM().transpose() };
	Vector3 AwrtNexpE { 
		-1.0 * Earth::mu * Earth::radius * Earth::radius * Earth::radius * Earth::J3
		/ ( 2.0 * _body->RwrtOmag7 ) * ( ( 15.0 * _body->RwrtOexpE[2] 
		- 35.0 * _body->RwrtOexpE[2] * _body->RwrtOexpE[2] * _body->RwrtOexpE[2] 
		/ _body->RwrtOmag2 ) * _body->RwrtOexpE + ( 15.0 * _body->RwrtOexpE[2] 
		* _body->RwrtOexpE[2] - 3.0 * _body->RwrtOmag2 ) * Z_UNIT_VECTOR3 )
	};

	return CfromEtoN * AwrtNexpE;
	
}

/*
** ----------- Class Definition ------------
*/ 
// constructor
J4Dynamics::J4Dynamics(SpacecraftBody* body) :
	Dynamics(body)
{

}

const Vector3 J4Dynamics::getAwrtNexpN()
{
	Matrix3 CfromEtoN { _body->CfromNtoE.getDCM().transpose() };
	Vector3 AwrtNexpE { 
		-5.0 * Earth::mu * Earth::radius * Earth::radius * Earth::radius * Earth::radius
		* Earth::J4 / ( 8.0 * _body->RwrtOmag9 ) * ( ( 42.0 * _body->RwrtOexpE[2] * _body->RwrtOexpE[2]
		- 3.0 * _body->RwrtOmag2 - 63.0 * _body->RwrtOexpE[2] * _body->RwrtOexpE[2]
		* _body->RwrtOexpE[2] * _body->RwrtOexpE[2] / _body->RwrtOmag2 )
		* _body->RwrtOexpE + ( 28.0 * _body->RwrtOexpE[2] * _body->RwrtOexpE[2] * _body->RwrtOexpE[2]
		- 12.0 * _body->RwrtOexpE[2] * _body->RwrtOmag2 ) * Z_UNIT_VECTOR3 )
	};

	return CfromEtoN * AwrtNexpE;
	
}
