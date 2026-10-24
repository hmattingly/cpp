/*
** ------------ Header Guard -------------
*/ 
#ifndef COORDINATETRANSFORM_HH  
#define COORDINATETRANSFORM_HH

/*
** ------- Preprocessor directives -------
*/ 
#include "Vector.hh"
#include "Constants.hh"
#include "CelestialBody.hh"
#include "FrameTransform.hh"

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

namespace CoordinateTransform
{	
	const Vector3 geth(const Vector3& RwrtOexpN, const Vector3& VwrtOexpN)
	{
		return Vector3 { cross( RwrtOexpN, VwrtOexpN ) };
	}

	const Vector3 getnHat(const Vector3& h)
	{
		if ( ( h - Z_UNIT_VECTOR3 ).mag() < FLOAT_TOL )  // equatorial orbit
		{
			return Vector3 { X_UNIT_VECTOR3 };
		}
		else
		{
			return Vector3 { cross( Z_UNIT_VECTOR3, h ).unit() };
		}
	}

	const Vector3 getEcc(const Vector3& RwrtOexpN, const Vector3& VwrtOexpN)
	{
		double RwrtOexpNmag { RwrtOexpN.mag() };
		double VwrtOexpNmag { VwrtOexpN.mag() };

		return Vector3 {
			( ( VwrtOexpNmag * VwrtOexpNmag - EARTH.mu / RwrtOexpNmag ) 
			* RwrtOexpN - dot( RwrtOexpN, VwrtOexpN ) * VwrtOexpN ) / EARTH.mu
		};
	}

	const double geta(const Vector3& RwrtOexpN, const Vector3& VwrtOexpN, const double& eccMag)
	{
		double RwrtOexpNmag { RwrtOexpN.mag() };
		double VwrtOexpNmag { VwrtOexpN.mag() };

		if ( ABS( 1.0 - eccMag ) < FLOAT_TOL )  // parabolic orbit
		{
			return MAX_DOUBLE;
		}
		else
		{
			return -1.0 * EARTH.mu * RwrtOexpNmag / ( VwrtOexpNmag * VwrtOexpNmag * RwrtOexpNmag - 2.0 * EARTH.mu );
		}
	}

	// left off at inc

	const Vector6 N2kepoe(const Vector3& RwrtOexpN, const Vector3& VwrtOexpN)
	{		
		// position and velocity terms
		double RwrtOexpNmag { RwrtOexpN.mag() };
		Vector3 RwrtOexpNhat { RwrtOexpN / RwrtOexpNmag };
		double VwrtOexpNmag { VwrtOexpN.mag() };

		// specific angular momentum
		Vector3 h { geth( RwrtOexpN, VwrtOexpN ) };
		double hMag { h.mag() };
		Vector3 hHat { h / hMag };

		// line of nodes
		Vector3 nHat { getnHat( h ) };

		// eccentricity
		Vector3 ecc { getEcc( RwrtOexpN, VwrtOexpN ) };
		double eccMag { ecc.mag() };

		// semi-major axis
		double a { geta( RwrtOexpN, VwrtOexpN, eccMag ) };

		// inclination
		double inc { std::acos( hHat[2] ) };

		// right ascension of the ascending node
		double raan;
		if ( ABS( inc ) < FLOAT_TOL ) // equatorial orbit
		{
			raan = 0.0;  // RAAN undefined
		}
		else 
		{
			if ( nHat[1] < 0.0 )
			{
				raan = TWO_PI - std::acos( nHat[0] );
			}
			else if ( nHat[1] > 0.0 )
			{
				raan = std::acos( nHat[0] );
			}
		}

		// argument of periapsis
		double aop;
		if ( eccMag < FLOAT_TOL || ABS( inc ) < FLOAT_TOL )  // circular or equatorial orbit
		{
			aop = 0.0;  // AOP undefined
		}
		else
		{
			if ( ecc[2] < 0.0 )
			{
				aop = TWO_PI - std::acos( dot( nHat, ecc / eccMag ) );
			}
			else
			{
				aop = std::acos( dot( nHat, ecc / eccMag ) );
			}
		}

		// determine true longitude, argument of latitude, or true anomaly
		double theta;

		// true longitude (ecc = 0 and inc = 0)
		if ( eccMag < FLOAT_TOL && ABS( inc ) < FLOAT_TOL )
		{
			if ( RwrtOexpN[1] < 0.0 )
			{
				theta = TWO_PI - std::acos( RwrtOexpN[0] / RwrtOexpNmag );
			}
			else
			{
				theta = std::acos( RwrtOexpN[0] / RwrtOexpNmag );
			}
		}
		// true longitude of periapsis (ecc != 0, inc = 0)
		else if ( eccMag > FLOAT_TOL && ABS( inc ) < FLOAT_TOL )
		{
			if ( ecc[1] < 0.0 )
			{
				theta = TWO_PI - std::acos( ecc[0] / eccMag );
			}
			else
			{
				theta = std::acos( ecc[0] / eccMag );
			}
		}
		// argument of latitude (ecc = 0, inc != 0)
		else if ( eccMag < FLOAT_TOL && ABS( inc ) >= FLOAT_TOL )
		{
			if ( RwrtOexpN[2] < 0.0 )
			{
				theta = TWO_PI - std::acos( dot( nHat, RwrtOexpNhat ) );
			}
			else
			{
				theta = std::acos( dot( nHat, RwrtOexpNhat ) );
			}
		}
		// true anomaly
		else 
		{
			// prevent numerical errors near TA = 0
			double EdotR { dot( ecc / eccMag, RwrtOexpNhat ) };
			EdotR = MAX( -1.0, MIN( 1.0, EdotR ) );

			if ( dot( RwrtOexpN, VwrtOexpN ) < 0.0 )
			{
				theta = TWO_PI - std::acos( EdotR );
			}
			else
			{
				theta = std::acos( EdotR );
			}
		}

		return Vector6 { a,	eccMag, inc, raan, aop,	theta };
	}


	const Vector6 kepoe2N(double a, 
						  double eccMag,
					  	  double inc,
					  	  double raan,
					  	  double aop,
					  	  double theta)
	{
		assert(eccMag >= 0.0);

		double cTheta { std::cos( theta ) };
		double sTheta { std::sin( theta ) };

		// account for circular orbits
		if ( 0.0 == eccMag && 0.0 == inc )
		{
			aop = 0.0;
			raan = 0.0;
		}
		else if ( 0.0 == eccMag )
		{
			aop = 0.0;
		}

		// semi-latus rectum
		double p;
		if ( eccMag >= 0.0 && eccMag < 1.0 )
		{
			p = a * ( 1 - eccMag * eccMag );
		}
		else if ( eccMag == 1.0 )
		{
			p = 2.0 * a;
		}
		else
		{
			p = ABS( a ) * ( eccMag * eccMag - 1.0 );
		}

		// radius in perifocal frame
		Vector3 RwrtOexpP { ZERO_VECTOR3 };
		RwrtOexpP[0] = p * cTheta / ( 1.0 + eccMag * cTheta );
		RwrtOexpP[1] = p * sTheta / ( 1.0 + eccMag * cTheta );

		// velocity in perifocal frame
		Vector3 VwrtOexpP { ZERO_VECTOR3 };
		double sqrtMuOP { std::sqrt( EARTH.mu / p ) };
		VwrtOexpP[0] = -1.0 * sqrtMuOP * sTheta;
		VwrtOexpP[1] = sqrtMuOP * ( eccMag + cTheta );

		// transform to ECI frame
		FrameTransform CfromPtoN;
		CfromPtoN.setP2N( inc, raan, aop );
		Vector3 RwrtOexpN = CfromPtoN.getDCM() * RwrtOexpP;
		Vector3 VwrtOexpN = CfromPtoN.getDCM() * VwrtOexpP;

		return Vector6 { RwrtOexpN[0],
						RwrtOexpN[1],
						RwrtOexpN[2],
						VwrtOexpN[0],
						VwrtOexpN[1],
						VwrtOexpN[2] };
	}

	const Vector6 kepoe2N(const Vector6& state)
	{
		return kepoe2N( state[0], state[1], state[2], state[3], state[4], state[5] );
	}
};

#endif  // COORDINATETRANSFORM_HH
