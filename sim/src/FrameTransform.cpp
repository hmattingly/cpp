/*
** ------- Preprocessor directives -------
*/ 
#include "FrameTransform.hh"
#include "Matrix.hh"
#include "CelestialBody.hh"
#include "Constants.hh"
#include <cmath>	// for std::sqrt(), std::acos(), etc.
#include <cassert>	// for assert
#include <cstddef>  // for std::size_t

/*
** -------------- Constants ---------------
*/ 

/*
** -------- Forward Declarations ----------
*/ 

/*
** --------- Namespace directives ---------
*/ 
using namespace Constants;

// reference definitions
  // O = Center of Earth
  // B = Center of Mass of Body
  // S = Center of Mass of Earth Observer
// frame definitions
  // N = ECI
  // E = ECEF
  // P = Perifocal
  // L = LVLH / RTN
  // T = topocentric (SEZ / SEU)
  // D = NED

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

// Euler a-b-c = Rotc(psi)*Rotb(theta)*Rota(phi)
  // phi = first rotation angle
  // theta = second rotation angle
  // psi = third rotation angle

  // a = first rotation axis
  // b = second rotation axis
  // c = third rotation axis

void FrameTransform::setEulerAngles121(const double& phi, const double& theta, const double& psi)
{
	_dcm = FrameTransform::getRot1( psi ) * FrameTransform::getRot2( theta ) * FrameTransform::getRot1( phi );
}

void FrameTransform::setEulerAngles123(const double& phi, const double& theta, const double& psi)
{
	_dcm = FrameTransform::getRot3( psi ) * FrameTransform::getRot2( theta ) * FrameTransform::getRot1( phi );
}

void FrameTransform::setEulerAngles131(const double& phi, const double& theta, const double& psi)
{
	_dcm = FrameTransform::getRot1( psi ) * FrameTransform::getRot3( theta ) * FrameTransform::getRot1( phi );
}

void FrameTransform::setEulerAngles132(const double& phi, const double& theta, const double& psi)
{
	_dcm = FrameTransform::getRot2( psi ) * FrameTransform::getRot3( theta ) * FrameTransform::getRot1( phi );
}

void FrameTransform::setEulerAngles212(const double& phi, const double& theta, const double& psi)
{
	_dcm = FrameTransform::getRot2( psi ) * FrameTransform::getRot1( theta ) * FrameTransform::getRot2( phi );
}

void FrameTransform::setEulerAngles213(const double& phi, const double& theta, const double& psi)
{
	_dcm = FrameTransform::getRot3( psi ) * FrameTransform::getRot1( theta ) * FrameTransform::getRot2( phi );
}

void FrameTransform::setEulerAngles231(const double& phi, const double& theta, const double& psi)
{
	_dcm = FrameTransform::getRot1( psi ) * FrameTransform::getRot3( theta ) * FrameTransform::getRot2( phi );
}

void FrameTransform::setEulerAngles232(const double& phi, const double& theta, const double& psi)
{
	_dcm = FrameTransform::getRot2( psi ) * FrameTransform::getRot3( theta ) * FrameTransform::getRot2( phi );
}

void FrameTransform::setEulerAngles312(const double& phi, const double& theta, const double& psi)
{
	_dcm = FrameTransform::getRot2( psi ) * FrameTransform::getRot1( theta ) * FrameTransform::getRot3( phi );
}

void FrameTransform::setEulerAngles313(const double& phi, const double& theta, const double& psi)
{
	_dcm = FrameTransform::getRot3( psi ) * FrameTransform::getRot1( theta ) * FrameTransform::getRot3( phi );
}

void FrameTransform::setEulerAngles321(const double& phi, const double& theta, const double& psi)
{
	_dcm = FrameTransform::getRot1( psi ) * FrameTransform::getRot2( theta ) * FrameTransform::getRot3( phi );
}

void FrameTransform::setEulerAngles323(const double& phi, const double& theta, const double& psi)
{
	_dcm = FrameTransform::getRot3( psi ) * FrameTransform::getRot2( theta ) * FrameTransform::getRot3( phi );
}

void FrameTransform::setEulerAngles12(const double& phi, const double& theta)
{
	_dcm = FrameTransform::getRot2( theta ) * FrameTransform::getRot1( phi );
}

void FrameTransform::setEulerAngles21(const double& phi, const double& theta)
{
	_dcm = FrameTransform::getRot1( theta ) * FrameTransform::getRot2( phi );
}

void FrameTransform::setEulerAngles13(const double& phi, const double& theta)
{
	_dcm = FrameTransform::getRot3( theta ) * FrameTransform::getRot1( phi );
}

void FrameTransform::setEulerAngles31(const double& phi, const double& theta)
{
	_dcm = FrameTransform::getRot1( theta ) * FrameTransform::getRot3( phi );
}

void FrameTransform::setEulerAngles32(const double& phi, const double& theta)
{
	_dcm = FrameTransform::getRot2( theta ) * FrameTransform::getRot3( phi );
}

void FrameTransform::setEulerAngles23(const double& phi, const double& theta)
{
	_dcm = FrameTransform::getRot3( theta ) * FrameTransform::getRot2( phi );
}

// LVLH to ECI
void FrameTransform::setL2N(const double& inc, const double& raan, const double& aol)
{
	setEulerAngles313( -1.0 * aol, -1.0 * inc, -1.0 * raan );
}

// ECI to LVLH
void FrameTransform::setN2L(const double& inc, const double& raan, const double& aol)
{
	setEulerAngles313( raan, inc, aol );
}

// Perifocal to ECI
void FrameTransform::setP2N(const double& inc, const double& raan, const double& aop)
{
	setEulerAngles313( -1.0 * aop, -1.0 * inc, -1.0 * raan );
}

// ECI to Perifocal
void FrameTransform::setN2P(const double& inc, const double& raan, const double& aop)
{
	setEulerAngles313( raan, inc, aop );
}

// NED to ECI
void FrameTransform::setD2N(const double& gdLat, const double& st)
{
	setEulerAngles23( gdLat + PI / 2.0, -1.0 * st );
}

// ECI to NED
void FrameTransform::setN2D(const double& gdLat, const double& st)
{
	setEulerAngles32( st, -1.0 * ( gdLat + PI / 2.0 ) );
}

// Tropocentric (SEZ) to ECI
void FrameTransform::setT2N(const double& gdLat, const double& st)
{
	setEulerAngles23( gdLat - PI / 2.0, -1.0 * st );
}

// ECI to Tropocentric (SEZ)
void FrameTransform::setN2T(const double& gdLat, const double& st)
{
	setEulerAngles32( st, PI / 2.0 - gdLat );
}

// ECEF to ECI
void FrameTransform::setE2N(Earth* pEarth)
{
	_dcm = pEarth->getPrecessionDCM().transpose()
		   * pEarth->getNutationDCM().transpose()
		   * pEarth->getEarthRotationDCM().transpose() 
		   * pEarth->getPolarMotionDCM().transpose();
}

// ECI to ECEF
void FrameTransform::setN2E(Earth* pEarth)
{
	_dcm = pEarth->getPolarMotionDCM() 
		   * pEarth->getEarthRotationDCM()
		   * pEarth->getNutationDCM()
		   * pEarth->getPrecessionDCM();
}

// NED to ECEF
void FrameTransform::setD2E(const double& gdLat, const double& lon)
{
	setEulerAngles23( gdLat + PI / 2.0, -1.0 * lon );
}

// ECEF to NED
void FrameTransform::setE2D(const double& gdLat, const double& lon)
{
	setEulerAngles32( lon, -1.0 * ( gdLat + PI / 2.0 ) );
}

// Tropocentric (SEZ) to ECEF
void FrameTransform::setT2E(const double& gdLat, const double& lon)
{
	setEulerAngles23( gdLat - PI / 2.0, -1.0 * lon );
}

// ECEF to Tropocentric (SEZ)
void FrameTransform::setE2T(const double& gdLat, const double& lon)
{
	setEulerAngles32( lon, PI / 2.0 - gdLat );
}

// NED to Tropocentric (SEZ)
void FrameTransform::setD2T()
{
	_dcm = {
		{ -1.0, 0.0, 0.0 },
		{ 0.0, 1.0, 0.0 },
		{ 0.0, 0.0, -1.0 }
	};
}

// Tropocentric (SEZ) to NED
void FrameTransform::setT2D()
{
	_dcm = {
		{ -1.0, 0.0, 0.0 },
		{ 0.0, 1.0, 0.0 },
		{ 0.0, 0.0, -1.0 }
	};
}
