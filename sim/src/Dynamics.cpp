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
Dynamics::Dynamics(SpacecraftBody* pBody) :
	_pBody { pBody }
{

}

/*
** ----------- Class Definition ------------
*/ 
// constructor
TwoBodyDynamics::TwoBodyDynamics(SpacecraftBody* pBody, Earth* pEarth) :
	Dynamics(pBody), _pEarth { pEarth }
{

}

const Vector3 TwoBodyDynamics::getAofBwrtIexpI()
{
	return ( -1.0 * Earth::mu / _pBody->RofBwrtCmag3 * _pBody->RofBwrtCexpI );
}

/*
** ----------- Class Definition ------------
*/ 
// constructor
J2Dynamics::J2Dynamics(SpacecraftBody* pBody, Earth* pEarth) :
	Dynamics(pBody), _pEarth { pEarth }
{

}

const Vector3 J2Dynamics::getAofBwrtIexpI()
{
	return ( -1.5 * Earth::mu * Earth::radius * Earth::radius * Earth::J2
			 / _pBody->RofBwrtCmag5
			 * ( _pBody->RofBwrtCexpI + 2.0 * _pBody->RofBwrtCexpI[2] * Z_UNIT_VECTOR3
			 - 5.0 * _pBody->RofBwrtCexpI[2] * _pBody->RofBwrtCexpI[2]
			 * _pBody->RofBwrtCexpI / _pBody->RofBwrtCmag2 ) );
}

/*
** ----------- Class Definition ------------
*/ 
// constructor
J3Dynamics::J3Dynamics(SpacecraftBody* pBody, Earth* pEarth) :
	Dynamics(pBody), _pEarth { pEarth }
{

}

const Vector3 J3Dynamics::getAofBwrtIexpI()
{
	Vector3 AofBwrtIexpE { 
		-1.0 * Earth::mu * Earth::radius * Earth::radius * Earth::radius * Earth::J3
		/ ( 2.0 * _pBody->RofBwrtCmag7 ) * ( ( 15.0 * _pBody->RofBwrtCexpE[2] 
		- 35.0 * _pBody->RofBwrtCexpE[2] * _pBody->RofBwrtCexpE[2] * _pBody->RofBwrtCexpE[2] 
		/ _pBody->RofBwrtCmag2 ) * _pBody->RofBwrtCexpE + ( 15.0 * _pBody->RofBwrtCexpE[2] 
		* _pBody->RofBwrtCexpE[2] - 3.0 * _pBody->RofBwrtCmag2 ) * Z_UNIT_VECTOR3 )
	};

	return _pEarth->getCfromEtoI() * AofBwrtIexpE;
	
}

/*
** ----------- Class Definition ------------
*/ 
// constructor
J4Dynamics::J4Dynamics(SpacecraftBody* pBody, Earth* pEarth) :
	Dynamics(pBody), _pEarth { pEarth }
{

}

const Vector3 J4Dynamics::getAofBwrtIexpI()
{
	Vector3 AofBwrtIexpE { 
		-5.0 * Earth::mu * Earth::radius * Earth::radius * Earth::radius * Earth::radius
		* Earth::J4 / ( 8.0 * _pBody->RofBwrtCmag9 ) * ( ( 42.0 * _pBody->RofBwrtCexpE[2] * _pBody->RofBwrtCexpE[2]
		- 3.0 * _pBody->RofBwrtCmag2 - 63.0 * _pBody->RofBwrtCexpE[2] * _pBody->RofBwrtCexpE[2]
		* _pBody->RofBwrtCexpE[2] * _pBody->RofBwrtCexpE[2] / _pBody->RofBwrtCmag2 )
		* _pBody->RofBwrtCexpE + ( 28.0 * _pBody->RofBwrtCexpE[2] * _pBody->RofBwrtCexpE[2] * _pBody->RofBwrtCexpE[2]
		- 12.0 * _pBody->RofBwrtCexpE[2] * _pBody->RofBwrtCmag2 ) * Z_UNIT_VECTOR3 )
	};

	return _pEarth->getCfromEtoI() * AofBwrtIexpE;
	
}

/*
** ----------- Class Definition ------------
*/ 
// constructor
DragDynamics::DragDynamics(SpacecraftBody* pBody, Earth* pEarth) :
	Dynamics(pBody), _pEarth { pEarth }
{

}

const Vector3 DragDynamics::getAofBwrtIexpI()
{
	_rho = Earth::getDensity( _pBody->alt );

	return (
		-1.0 * 0.5 * _pBody->Cd * _pBody->AMR * _rho * _pBody->VofBwrtEexpI.mag() * _pBody->VofBwrtEexpI * KM2M
	);
	
}

/*
** ----------- Class Definition ------------
*/ 
// constructor
SunDynamics::SunDynamics(SpacecraftBody* pBody, Sun* pSun) :
	Dynamics(pBody), _pSun { pSun }
{

}

const Vector3 SunDynamics::getAofBwrtIexpI()
{
	// calculate s/c to sun position vector
	Vector3 RofSwrtBexpI { _pSun->getRofSwrtCexpI() - _pBody->RofBwrtCexpI };
	double RofSwrtBmag { RofSwrtBexpI.mag() };
	double RofSwrtBmag3 { RofSwrtBmag * RofSwrtBmag * RofSwrtBmag };
	double RofSwrtCmag3 { _pSun->getRofSwrtCmag() * _pSun->getRofSwrtCmag() * _pSun->getRofSwrtCmag() };

	return _pSun->mu * ( RofSwrtBexpI / RofSwrtBmag3 - _pSun->getRofSwrtCexpI() / RofSwrtCmag3 );
}

/*
** ----------- Class Definition ------------
*/ 
// constructor
SrpDynamics::SrpDynamics(SpacecraftBody* pBody, Sun* pSun) :
	Dynamics(pBody), _pSun { pSun }
{

}

const Vector3 SrpDynamics::getAofBwrtIexpI()
{
	// calculate s/c to sun position vector
	Vector3 RofSwrtBexpI { _pSun->getRofSwrtCexpI() - _pBody->RofBwrtCexpI };
	double RofSwrtBmag { RofSwrtBexpI.mag() };
	Vector3 RofSwrtBexpIhat { RofSwrtBexpI.unit() };

	double scale { ( AU2KM * AU2KM ) / ( RofSwrtBmag * RofSwrtBmag ) };
	double Ctilde { .25 + ( 1.0 / 9.0 ) * _pBody->CRd }; 

	return -1.0 * _pBody->AMR * M2KM * M2KM * scale * Ctilde * ( _pSun->E / c ) * RofSwrtBexpIhat;
}
