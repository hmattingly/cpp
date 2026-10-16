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
Dynamics::Dynamics(SpacecraftBody& body) :
	_body { body }
{

}

TwoBodyDynamics::TwoBodyDynamics(SpacecraftBody& body) :
	Dynamics(body)
{

}

void TwoBodyDynamics::calcAwrtOexpN()
{
	double rmag { _body.RwrtOexpN.mag() };
	_body.AwrtOexpN += -1.0 * EARTH.mu / (rmag * rmag * rmag) * _body.RwrtOexpN;
}
