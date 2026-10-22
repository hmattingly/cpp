/*
** ------- Preprocessor directives -------
*/ 
#include "Transform.hh"
#include "Matrix.hh"
#include "CelestialBody.hh"
#include "Constants.hh"
#include <cmath>	// for std::sqrt(), std::acos(), etc.

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
using namespace Constants;

/*
** ----------- Class Definition ------------
*/ 
Transform::Transform()
{
	
}

const Matrix3 Transform::rot1(const double& theta)
{
	return Matrix3 {
		{ 1.0, 0.0, 0.0 },
		{ 0.0, std::cos(theta), std::sin(theta) },
		{ 0.0, -1.0 * std::sin(theta), std::cos(theta) }
	};
}

const Matrix3 Transform::rot2(const double& theta)
{
	return Matrix3 {
		{ std::cos(theta), 0.0,  -1.0 * std::sin(theta) },
		{ 0.0, 1.0, 0.0 },
		{ std::sin(theta), 0.0, std::cos(theta) }
	};
}

const Matrix3 Transform::rot3(const double& theta)
{
	return Matrix3 {
		{ std::cos(theta), std::sin(theta), 0.0 },
		{ -1.0 * std::sin(theta), std::cos(theta), 0.0 },
		{ 0.0, 0.0, 1.0 }
	};
}

const Matrix3 lvlh2eci(const double& inc, const double& raan, const double& aol)
{
	return Matrix3 {
		Transform::rot3( -1.0 * raan )
		* Transform::rot1( -1.0 * inc )
		* Transform::rot3( -1.0 * aol )
	};
}

const Matrix3 eci2lvlh(const double& inc, const double& raan, const double& aol)
{
	Matrix3 mat { Transform::lvlh2eci(inc, raan, aol) };
	return mat.transpose();
}

const Vector6 eci2kep(const Vector3& r, const Vector3& v)
{
	// position and velocity terms
	double rMag { r.mag() };
	Vector3 rHat { r / rMag };
	double vMag { v.mag() };

	// specific angular momentum
	Vector3 h { cross( r, v ) };
	double hMag { h.mag() };
	Vector3 hHat { h / hMag };

	// line of nodes
	Vector3 nHat { cross( Z_UNIT_VECTOR3, h ).unit() };

	// eccentricity
	Vector3 ecc { ( ( vMag * vMag - EARTH.mu / rMag ) * r - dot( r, v ) * v ) / EARTH.mu };
	double eccMag { ecc.mag() };
	Vector3 eccHat { ecc / eccMag };

	// semi-major axis
	double a;
	if ( 1.0 == eccMag )
	{
		a = MAX_DOUBLE;
	}
	else
	{
		a = -1.0 * EARTH.mu * rMag / ( vMag * vMag * rMag - 2.0 * EARTH.mu );
	}

	// inclination
	double inc { std::acos( hHat[2] ) };

	// right ascension of the ascending node
	double raan;
	if ( nHat[1] < 0.0 )
	{
		raan = TWO_PI - std::acos( nHat[0] );
	}
	else
	{
		raan = std::acos( nHat[0] );
	}

	// argument of periapsis
	double aop;
	if ( eccHat[2] < 0.0 )
	{
		aop = TWO_PI - std::acos( dot( nHat, eccHat ) );
	}
	else
	{
		aop = std::acos( dot( nHat, eccHat ) );
	}

	// determine true longitude, argument of latitude, or true anomaly
	double theta;

	  // true longitude
	if ( std::abs( eccMag ) < FLOAT_TOL & std::abs( inc ) < FLOAT_TOL )
	{
		if ( r[1] < 0.0 )
		{
			theta = TWO_PI - std::acos( r[0] / rMag );
		}
		else
		{
			theta = std::acos( r[0] / rMag );
		}
	}

	  // argument of latitude
	if ( std::abs( eccMag ) < FLOAT_TOL )
	{
		if ( r[2] < 0.0 )
		{
			theta = TWO_PI - std::acos( dot( nHat, rHat ) );
		}
		else
		{
			theta = std::acos( dot( nHat, rHat ) );
		}
	}

	  // true anomaly
	else 
	{
		// prevent numerical errors near TA = 0
		double angle { dot( eccHat, rHat ) };
		angle = MAX( -1.0, MIN( 1.0, angle ) );

		if ( dot( r, v ) < 0.0 )
		{
			theta = TWO_PI - std::acos( angle );
		}
		else
		{
			theta = std::acos( angle );
		}
	}

	return Vector6 { a,	eccMag, inc, raan, aop,	theta };
}
