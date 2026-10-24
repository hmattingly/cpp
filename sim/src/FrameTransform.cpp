/*
** ------- Preprocessor directives -------
*/ 
#include "FrameTransform.hh"
#include "Matrix.hh"
#include <cmath>	// for std::sqrt(), std::acos(), etc.
#include <cassert>	// for assert

/*
** -------------- Constants ---------------
*/ 

/*
** -------- Forward Declarations ----------
*/ 

/*
** --------- Namespace directives ---------
*/ 

// frame definitions
  // N = ECI
  // E = ECEF
  // P = Perifocal
  // L = LVLH / RTN

/*
** ----------- Class Definition ------------
*/ 
FrameTransform::FrameTransform(const Matrix3& dcm) :
	_dcm { dcm }
{
	
}

const Matrix3 FrameTransform::getRot1(const double& theta)
{
	double cTheta { std::cos( theta ) };
	double sTheta { std::sin( theta ) };

	return Matrix3 {
		{ 1.0, 0.0, 0.0 },
		{ 0.0, cTheta, sTheta },
		{ 0.0, -1.0 * sTheta, cTheta }
	};
}

const Matrix3 FrameTransform::getRot2(const double& theta)
{
	double cTheta { std::cos( theta ) };
	double sTheta { std::sin( theta ) };

	return Matrix3 {
		{ cTheta, 0.0,  -1.0 * sTheta },
		{ 0.0, 1.0, 0.0 },
		{ sTheta, 0.0, cTheta }
	};
}

const Matrix3 FrameTransform::getRot3(const double& theta)
{
	double cTheta { std::cos( theta ) };
	double sTheta { std::sin( theta ) };

	return Matrix3 {
		{ cTheta, sTheta, 0.0 },
		{ -1.0 * sTheta, cTheta, 0.0 },
		{ 0.0, 0.0, 1.0 }
	};
}

void FrameTransform::setEulerAngles121(const double& psi, const double& theta, const double& phi)
{
	_dcm = FrameTransform::getRot1( phi ) * FrameTransform::getRot2( theta ) * FrameTransform::getRot1( psi );
}

void FrameTransform::setEulerAngles123(const double& psi, const double& theta, const double& phi)
{
	_dcm = FrameTransform::getRot3( phi ) * FrameTransform::getRot2( theta ) * FrameTransform::getRot1( psi );
}

void FrameTransform::setEulerAngles131(const double& psi, const double& theta, const double& phi)
{
	_dcm = FrameTransform::getRot1( phi ) * FrameTransform::getRot3( theta ) * FrameTransform::getRot1( psi );
}

void FrameTransform::setEulerAngles132(const double& psi, const double& theta, const double& phi)
{
	_dcm = FrameTransform::getRot2( phi ) * FrameTransform::getRot3( theta ) * FrameTransform::getRot1( psi );
}

void FrameTransform::setEulerAngles212(const double& psi, const double& theta, const double& phi)
{
	_dcm = FrameTransform::getRot2( phi ) * FrameTransform::getRot1( theta ) * FrameTransform::getRot2( psi );
}

void FrameTransform::setEulerAngles213(const double& psi, const double& theta, const double& phi)
{
	_dcm = FrameTransform::getRot3( phi ) * FrameTransform::getRot1( theta ) * FrameTransform::getRot2( psi );
}

void FrameTransform::setEulerAngles231(const double& psi, const double& theta, const double& phi)
{
	_dcm = FrameTransform::getRot1( phi ) * FrameTransform::getRot3( theta ) * FrameTransform::getRot2( psi );
}

void FrameTransform::setEulerAngles232(const double& psi, const double& theta, const double& phi)
{
	_dcm = FrameTransform::getRot2( phi ) * FrameTransform::getRot3( theta ) * FrameTransform::getRot2( psi );
}

void FrameTransform::setEulerAngles312(const double& psi, const double& theta, const double& phi)
{
	_dcm = FrameTransform::getRot2( phi ) * FrameTransform::getRot1( theta ) * FrameTransform::getRot3( psi );
}

void FrameTransform::setEulerAngles313(const double& psi, const double& theta, const double& phi)
{
	_dcm = FrameTransform::getRot3( phi ) * FrameTransform::getRot1( theta ) * FrameTransform::getRot3( psi );
}

void FrameTransform::setEulerAngles321(const double& psi, const double& theta, const double& phi)
{
	_dcm = FrameTransform::getRot1( phi ) * FrameTransform::getRot2( theta ) * FrameTransform::getRot3( psi );
}

void FrameTransform::setEulerAngles323(const double& psi, const double& theta, const double& phi)
{
	_dcm = FrameTransform::getRot3( phi ) * FrameTransform::getRot2( theta ) * FrameTransform::getRot3( psi );
}

void FrameTransform::setL2N(const double& inc, const double& raan, const double& aol)
{
	setEulerAngles313( -1.0 * aol, -1.0 * inc, -1.0 * raan );
}

void FrameTransform::setN2L(const double& inc, const double& raan, const double& aol)
{
	setEulerAngles313( raan, inc, aol );
}

void FrameTransform::setP2N(const double& inc, const double& raan, const double& aop)
{
	setEulerAngles313( -1.0 * aop, -1.0 * inc, -1.0 * raan );
}

void FrameTransform::setN2P(const double& inc, const double& raan, const double& aop)
{
	setEulerAngles313( raan, inc, aop );
}

void FrameTransform::setE2N(const double& gmst)
{
	_dcm = FrameTransform::getRot3( -1.0 * gmst );
}

void FrameTransform::setN2E(const double& gmst)
{
	_dcm = FrameTransform::getRot3( gmst );
}
