/*
** ------- Preprocessor directives -------
*/ 
#include "Dynamics.hh"
#include "Vector.hh"
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
	return ( -1.0 * EARTH.mu / _body->RwrtOexpNmag3 * _body->RwrtOexpN );
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
			 / _body->RwrtOexpNmag5
			 * ( _body->RwrtOexpN + 2.0 * _body->RwrtOexpN[2] * Z_UNIT_VECTOR3
			 - 5.0 * _body->RwrtOexpN[2] * _body->RwrtOexpN[2]
			 * _body->RwrtOexpN / _body->RwrtOexpNmag2 ) );
}

