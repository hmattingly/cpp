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
#include <cmath>	// for std::sqrt(), std::acos(), etc.
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
using namespace Constants;

namespace CoordinateTransform
{	
	// specific angular momentum (HofBwrtCexpI) vector given ECI position and velocity
	inline const Vector3 getSpecAngularMomentum(const Vector3& RofBwrtCexpI, const Vector3& VofBwrtIexpI)
	{
		return Vector3 { cross( RofBwrtCexpI, VofBwrtIexpI ) };
	}

	// line of nodes unit vector (NofBwrtCexpIhat) given ECI position and velocity
	inline const Vector3 getLineOfNodesUnit(const Vector3& RofBwrtCexpI, const Vector3& VofBwrtIexpI)
	{
		Vector3 HofBwrtCexpI { getSpecAngularMomentum( RofBwrtCexpI, VofBwrtIexpI ) };

		return Vector3 { cross( Z_UNIT_VECTOR3, HofBwrtCexpI ).unit() };
	}

	// (overload) line of nodes unit vector (NofBwrtCexpIhat) given specific angular momentum vector
	inline const Vector3 getLineOfNodesUnit(const Vector3& HofBwrtCexpI)
	{
		return Vector3 { cross( Z_UNIT_VECTOR3, HofBwrtCexpI ).unit() };
	}

	// eccentricity vector (EofBwrtCexpI) given ECI position and velocity
	inline const Vector3 getEccentricityVector(const Vector3& RofBwrtCexpI, const Vector3& VofBwrtIexpI)
	{
		double RofBwrtCmag { RofBwrtCexpI.mag() };
		double VofBwrtImag { VofBwrtIexpI.mag() };

		return Vector3 {
			( ( VofBwrtImag * VofBwrtImag - Earth::mu / RofBwrtCmag ) 
			* RofBwrtCexpI - dot( RofBwrtCexpI, VofBwrtIexpI ) * VofBwrtIexpI ) / Earth::mu
		};
	}

	// eccentricity magnitude (ecc) given ECI position and velocity
	inline const double getEccentricity(const Vector3& RofBwrtCexpI, const Vector3& VofBwrtIexpI)
	{
		return getEccentricityVector( RofBwrtCexpI, VofBwrtIexpI ).mag();
	}

	// semimajor axis (a) given ECI position and velocity
	inline const double getSemimajorAxis(const Vector3& RofBwrtCexpI, const Vector3& VofBwrtIexpI)
	{
		double RofBwrtCmag { RofBwrtCexpI.mag() };
		double VofBwrtImag { VofBwrtIexpI.mag() };
		double ecc { getEccentricity( RofBwrtCexpI, VofBwrtIexpI ) };

		if ( ABS( 1.0 - ecc ) < FLOAT_TOL )  // parabolic orbit
		{
			return MAX_DOUBLE;
		}
		else
		{
			return -1.0 * Earth::mu * RofBwrtCmag / ( VofBwrtImag * VofBwrtImag * RofBwrtCmag - 2.0 * Earth::mu );
		}
	}

	// (overload) semimajor axis (a) given ECI position and velocity magnitudes and eccentricity magnitude
	inline const double getSemimajorAxis(const double& RofBwrtCmag, const double& VofBwrtImag, const double& ecc)
	{
		if ( ABS( 1.0 - ecc ) < FLOAT_TOL )  // parabolic orbit
		{
			return MAX_DOUBLE;
		}
		else
		{
			return -1.0 * Earth::mu * RofBwrtCmag / ( VofBwrtImag * VofBwrtImag * RofBwrtCmag - 2.0 * Earth::mu );
		}
	}

	// semiminor axis (b) given ECI position and velocity
	inline const double getSemiminorAxis(const Vector3& RofBwrtCexpI, const Vector3& VofBwrtIexpI)
	{
		double a { getSemimajorAxis( RofBwrtCexpI, VofBwrtIexpI ) };
		double ecc { getEccentricity( RofBwrtCexpI, VofBwrtIexpI ) };

		return a * std::sqrt( 1.0 - ecc * ecc );
	}

	// (overload) semimajor axis (b) given semimajor axis and eccentricity
	inline const double getSemiminorAxis(const double& a, const double& ecc)
	{
		return a * std::sqrt( 1.0 - ecc * ecc );
	}

	// semilatus rectum (p) given ECI position and velocity
	inline const double getSemilatusRectum(const Vector3& RofBwrtCexpI, const Vector3& VofBwrtIexpI)
	{
		double HofBwrtCmag { getSpecAngularMomentum( RofBwrtCexpI, VofBwrtIexpI ).mag() };
		
		return HofBwrtCmag * HofBwrtCmag / Earth::mu;
	}

	// (overload) semilatus rectum (p) given semimajor axis and eccentricity magnitude
	inline const double getSemilatusRectum(const double& a, const double& ecc)
	{
		if ( ecc >= 0.0 && ecc < 1.0 )
		{
			return a * ( 1 - ecc * ecc );
		}
		else
		{
			return ABS( a ) * ( ecc * ecc - 1.0 );
		}
	}

	// (overload) semilatus rectum (p) given specific angular momentum magnitude
	inline const double getSemilatusRectum(const double& HofBwrtCmag)
	{
		return HofBwrtCmag * HofBwrtCmag / Earth::mu;
	}

	// apoapsis (Ra) given ECI position and velocity
	inline const double getApoapsis(const Vector3& RofBwrtCexpI, const Vector3& VofBwrtIexpI)
	{
		double a { getSemimajorAxis( RofBwrtCexpI, VofBwrtIexpI) };
		double ecc { getEccentricity( RofBwrtCexpI, VofBwrtIexpI ) };

		if ( ecc >= 1.0 )
		{
			return MAX_DOUBLE;
		}
		else
		{
			return a * ( 1.0 + ecc );
		}
	}

	// (overload) apoapsis (Ra) given semilatus rectum and eccentricity magnitude
	inline const double getApoapsis(const double& p, const double& ecc)
	{
		if ( ecc >= 1.0 )
		{
			return MAX_DOUBLE;
		}
		else
		{
			return p / ( 1.0 - ecc );
		}
	}

	// periapsis (Rp) given ECI position and velocity
	inline const double getPeriapsis(const Vector3& RofBwrtCexpI, const Vector3& VofBwrtIexpI)
	{
		double p { getSemilatusRectum(RofBwrtCexpI, VofBwrtIexpI) };
		double ecc { getEccentricity( RofBwrtCexpI, VofBwrtIexpI ) };

		return p / ( 1.0 + ecc );
	}

	// (overload) periapsis (Rp) given semilatus rectum and eccentricity magnitude
	inline const double getPeriapsis(const double& p, const double& ecc)
	{
		return p / ( 1.0 + ecc );
	}

	// mean motion (n) given ECI position and velocity
	inline const double getMeanMotion(const Vector3& RofBwrtCexpI, const Vector3& VofBwrtIexpI)
	{
		double a { getSemimajorAxis( RofBwrtCexpI, VofBwrtIexpI) };
		assert(a > 0.0);

		return std::sqrt( Earth::mu / ( a * a * a ) );
	}

	// (overload) mean motion (n) given semimajor axis
	inline const double getMeanMotion(const double& a)
	{
		assert(a > 0.0);

		return std::sqrt( Earth::mu / ( a * a * a ) );
	}

	// specific energy (energy) given ECI position and velocity
	inline const double getSpecEnergy(const Vector3& RofBwrtCexpI, const Vector3& VofBwrtIexpI)
	{
		return 0.5 * VofBwrtIexpI.mag2() - Earth::mu / RofBwrtCexpI.mag();
	}

	// (overload) specific energy (energy) given semimajor axis
	inline const double getSpecEnergy(const double& a)
	{
		return -0.5 * Earth::mu / a;
	}

	// inclination (inc) given ECI position and velocity
	inline const double getInclination(const Vector3& RofBwrtCexpI, const Vector3& VofBwrtIexpI)
	{
		Vector3 HofBwrtCexpIhat { getSpecAngularMomentum( RofBwrtCexpI, VofBwrtIexpI ).unit() };
		
		return std::acos( HofBwrtCexpIhat[2] );
	}

	// (overload) inclination (inc) given specific angular momentum unit vector
	inline const double getInclination(const Vector3& HofBwrtCexpIhat)
	{
		return std::acos( HofBwrtCexpIhat[2] );
	}

	// right ascension of the ascending node (raan) given ECI position and velocity
	inline const double getRightAscension(const Vector3& RofBwrtCexpI, const Vector3& VofBwrtIexpI)
	{
		double inc { getInclination( RofBwrtCexpI, VofBwrtIexpI ) };
		Vector3 NofBwrtCexpIhat { getLineOfNodesUnit( RofBwrtCexpI, VofBwrtIexpI ) };

		if ( ABS( inc ) < FLOAT_TOL ) // equatorial orbit
		{
			return 0.0;  // RAAN undefined
		}
		else 
		{
			if ( NofBwrtCexpIhat[1] < 0.0 )
			{
				return TWO_PI - std::acos( NofBwrtCexpIhat[0] );
			}
			else
			{
				return std::acos( NofBwrtCexpIhat[0] );
			}
		}
	}

	// (overload) right ascension of the ascending node (raan) given inclination and line of nodes unit vector
	inline const double getRightAscension(const double& inc, const Vector3& NofBwrtCexpIhat)
	{
		if ( ABS( inc ) < FLOAT_TOL ) // equatorial orbit
		{
			return 0.0;  // RAAN undefined
		}
		else 
		{
			if ( NofBwrtCexpIhat[1] < 0.0 )
			{
				return TWO_PI - std::acos( NofBwrtCexpIhat[0] );
			}
			else
			{
				return std::acos( NofBwrtCexpIhat[0] );
			}
		}
	}

	// argument of periapsis (aop) given ECI position and velocity
	inline const double getArgumentOfPeriapsis(const Vector3& RofBwrtCexpI, const Vector3& VofBwrtIexpI)
	{
		Vector3 NofBwrtCexpIhat { getLineOfNodesUnit( RofBwrtCexpI, VofBwrtIexpI ) };
		Vector3 EofBwrtCexpI { getEccentricityVector( RofBwrtCexpI, VofBwrtIexpI ) };
		double ecc { EofBwrtCexpI.mag() };
		double inc { getInclination( RofBwrtCexpI, VofBwrtIexpI ) };
		
		if ( ecc < FLOAT_TOL || ABS( inc ) < FLOAT_TOL )  // circular or equatorial orbit
		{
			return 0.0;  // AOP undefined
		}
		else
		{
			if ( EofBwrtCexpI[2] < 0.0 )
			{
				return TWO_PI - std::acos( dot( NofBwrtCexpIhat, EofBwrtCexpI / ecc ) );
			}
			else
			{
				return std::acos( dot( NofBwrtCexpIhat, EofBwrtCexpI / ecc ) );
			}
		}
	}

	// (overload) argument of periapsis (aop) given inclination, eccentricity vector, and line of nodes unit vector
	inline const double getArgumentOfPeriapsis(const double& inc, const Vector3& EofBwrtCexpI, const Vector3& NofBwrtCexpIhat)
	{
		double ecc { EofBwrtCexpI.mag() };
		
		if ( ecc < FLOAT_TOL || ABS( inc ) < FLOAT_TOL )  // circular or equatorial orbit
		{
			return 0.0;  // AOP undefined
		}
		else
		{
			if ( EofBwrtCexpI[2] < 0.0 )
			{
				return TWO_PI - std::acos( dot( NofBwrtCexpIhat, EofBwrtCexpI / ecc ) );
			}
			else
			{
				return std::acos( dot( NofBwrtCexpIhat, EofBwrtCexpI / ecc ) );
			}
		}
	}

	// true anomaly (ta) given ECI position and velocity, and inclination, eccentricity vector, and line of nodes unit vector (optional)
	inline const double getTrueAnomaly(const Vector3& RofBwrtCexpI, const Vector3& VofBwrtIexpI, double inc=0.0, Vector3 EofBwrtCexpI=ZERO_VECTOR3, Vector3 NofBwrtCexpIhat=ZERO_VECTOR3)
	{
		if ( 0.0 == inc )
		{
			inc = getInclination( RofBwrtCexpI, VofBwrtIexpI );
		}
		if ( ZERO_VECTOR3 == EofBwrtCexpI )
		{
			EofBwrtCexpI = getEccentricityVector( RofBwrtCexpI, VofBwrtIexpI );
		}
		if ( ZERO_VECTOR3 == NofBwrtCexpIhat )
		{
			NofBwrtCexpIhat = getLineOfNodesUnit( RofBwrtCexpI, VofBwrtIexpI );
		}
		
		double ecc { EofBwrtCexpI.mag() };
		double RofBwrtCmag { RofBwrtCexpI.mag() };
		Vector3 RofBwrtCexpIhat { RofBwrtCexpI / RofBwrtCmag };

		// return true longitude (ecc = 0 and inc = 0)
		if ( ecc < FLOAT_TOL && ABS( inc ) < FLOAT_TOL )
		{
			if ( RofBwrtCexpI[1] < 0.0 )
			{
				return TWO_PI - std::acos( RofBwrtCexpI[0] / RofBwrtCmag );
			}
			else
			{
				return std::acos( RofBwrtCexpI[0] / RofBwrtCmag );
			}
		}
		// return true longitude of periapsis (ecc != 0, inc = 0)
		else if ( ecc > FLOAT_TOL && ABS( inc ) < FLOAT_TOL )
		{
			if ( EofBwrtCexpI[1] < 0.0 )
			{
				return TWO_PI - std::acos( EofBwrtCexpI[0] / ecc );
			}
			else
			{
				return std::acos( EofBwrtCexpI[0] / ecc );
			}
		}
		// return argument of latitude (ecc = 0, inc != 0)
		else if ( ecc < FLOAT_TOL && ABS( inc ) >= FLOAT_TOL )
		{
			if ( RofBwrtCexpI[2] < 0.0 )
			{
				return TWO_PI - std::acos( dot( NofBwrtCexpIhat, RofBwrtCexpIhat ) );
			}
			else
			{
				return std::acos( dot( NofBwrtCexpIhat, RofBwrtCexpIhat ) );
			}
		}
		// return true anomaly
		else 
		{
			// prevent numerical errors near TA = 0
			double EdotR { dot( EofBwrtCexpI / ecc, RofBwrtCexpIhat ) };
			EdotR = MAX( -1.0, MIN( 1.0, EdotR ) );

			if ( dot( RofBwrtCexpI, VofBwrtIexpI ) < 0.0 )
			{
				return TWO_PI - std::acos( EdotR );
			}
			else
			{
				return std::acos( EdotR );
			}
		}
	}

	// eccentric anomaly (E) given ECI position and velocity
	inline const double getEccentricAnomaly(const Vector3& RofBwrtCexpI, const Vector3& VofBwrtIexpI)
	{
		double ta { getTrueAnomaly( RofBwrtCexpI, VofBwrtIexpI ) };
		double ecc { getEccentricity( RofBwrtCexpI, VofBwrtIexpI ) };

		assert(ecc < 1.0);

		if ( 0.0 <= ta && ta <= PI )
		{
			return std::acos( ( ecc + std::cos( ta ) ) / ( 1.0 + ecc * std::cos( ta ) ) );
		}
		else
		{
			return TWO_PI - std::acos( ( ecc + std::cos( ta ) ) / ( 1.0 + ecc * std::cos( ta ) ) );
		}
	}

	// (overload) eccentric anomaly (E) given true anomaly and eccentricity magnitude
	inline const double getEccentricAnomaly(const double& ecc, const double& ta)
	{
		assert(ecc < 1.0);

		if ( 0.0 <= ta && ta <= PI )
		{
			return std::acos( ( ecc + std::cos( ta ) ) / ( 1.0 + ecc * std::cos( ta ) ) );
		}
		else
		{
			return TWO_PI - std::acos( ( ecc + std::cos( ta ) ) / ( 1.0 + ecc * std::cos( ta ) ) );
		}
	}

	// parabolic anomaly given ECI position and velocity
	inline const double getParabolicAnomaly(const Vector3& RofBwrtCexpI, const Vector3& VofBwrtIexpI)
	{
		double ta { getTrueAnomaly( RofBwrtCexpI, VofBwrtIexpI ) };
		double ecc { getEccentricity( RofBwrtCexpI, VofBwrtIexpI ) };

		assert(ABS( 1.0 - ecc ) < FLOAT_TOL);

		return std::tan( ta / 2.0 );
	}

	// (overload) parabolic anomaly given true anomaly and eccentricity magnitude
	inline const double getParabolicAnomaly(const double& ecc, const double& ta)
	{
		assert(ABS( 1.0 - ecc ) < FLOAT_TOL);

		return std::tan( ta / 2.0 );
	}

	// hyperbolic anomaly (H) given ECI position and velocity
	inline const double getHyperbolicAnomaly(const Vector3& RofBwrtCexpI, const Vector3& VofBwrtIexpI)
	{
		double ta { getTrueAnomaly( RofBwrtCexpI, VofBwrtIexpI ) };
		double ecc { getEccentricity( RofBwrtCexpI, VofBwrtIexpI ) };

		assert(ecc > 1.0);

		return std::asinh( ( std::sin( ta ) * std::sqrt( ecc * ecc - 1.0 ) ) / ( 1.0 + ecc * std::cos( ta ) ) );
	}

	// (overload) hyperbolic anomaly (H) given true anomaly and eccentricity magnitude
	inline const double getHyperbolicAnomaly(const double& ecc, const double& ta)
	{
		assert(ecc > 1.0);

		return std::asinh( ( std::sin( ta ) * std::sqrt( ecc * ecc - 1.0 ) ) / ( 1.0 + ecc * std::cos( ta ) ) );
	}

	// mean anomaly (M) given ECI position and velocity
	inline const double getMeanAnomaly(const Vector3& RofBwrtCexpI, const Vector3& VofBwrtIexpI)
	{
		double E { getEccentricAnomaly( RofBwrtCexpI, VofBwrtIexpI ) };
		double ecc { getEccentricity( RofBwrtCexpI, VofBwrtIexpI ) };

		return E - ecc * std::sin( E );
	}

	// (overload) mean anomaly (M) given eccentricity magnitude and eccentric anomaly
	inline const double getMeanAnomaly(const double& ecc, const double& E)
	{
		return E - ecc * std::sin( E );
	}

	// flight path angle (fpa) given ECI position and velocity
	inline const double getFlightPathAngle(const Vector3& RofBwrtCexpI, const Vector3& VofBwrtIexpI)
	{
		double HofBwrtCmag { getSpecAngularMomentum( RofBwrtCexpI, VofBwrtIexpI ).mag() };
		
		return std::atan2( dot( RofBwrtCexpI, VofBwrtIexpI), HofBwrtCmag );
	}

	// orbital period (P) given ECI position and velocity
	inline const double getPeriod(const Vector3& RofBwrtCexpI, const Vector3& VofBwrtIexpI)
	{
		double n { getMeanMotion( RofBwrtCexpI, VofBwrtIexpI ) };
		assert(n > 0.0);
		
		return TWO_PI / n;
	}

	// orbital period (P) given mean motion
	inline const double getPeriod(const double& n)
	{
		return TWO_PI / n;
	}

	
	// conversion from ECI position and velocity to keplerian orbial elements
	inline const Vector6 I2kepoe(const Vector3& RofBwrtCexpI, const Vector3& VofBwrtIexpI)
	{	
		// specific angular momentum
		Vector3 HofBwrtCexpI { getSpecAngularMomentum( RofBwrtCexpI, VofBwrtIexpI ) };

		// line of nodes
		Vector3 NofBwrtCexpIhat { getLineOfNodesUnit( HofBwrtCexpI ) };

		// eccentricity
		Vector3 EofBwrtCexpI { getEccentricityVector( RofBwrtCexpI, VofBwrtIexpI ) };
		double ecc { EofBwrtCexpI.mag() };

		// semi-major axis
		double a { getSemimajorAxis( RofBwrtCexpI.mag(), VofBwrtIexpI.mag(), ecc ) };

		// inclination
		double inc { getInclination( HofBwrtCexpI.unit() ) };

		// right ascension of the ascending node
		double raan { getRightAscension( inc, NofBwrtCexpIhat) };

		// argument of periapsis
		double aop { getArgumentOfPeriapsis( inc, EofBwrtCexpI, NofBwrtCexpIhat) };

		// determine true longitude, argument of latitude, or true anomaly
		double theta { getTrueAnomaly( RofBwrtCexpI, VofBwrtIexpI, inc, EofBwrtCexpI, NofBwrtCexpIhat ) };

		return Vector6 { a,	ecc, inc, raan, aop, theta };
	}

	// conversion keplerian orbial elements to ECI position and velocity
	inline const Vector6 kepoe2I(double a, 
						  double ecc,
					  	  double inc,
					  	  double raan,
					  	  double aop,
					  	  double theta)
	{
		assert(ecc >= 0.0);

		double cTheta { std::cos( theta ) };
		double sTheta { std::sin( theta ) };

		// account for circular orbits
		if ( 0.0 == ecc && 0.0 == inc )
		{
			aop = 0.0;
			raan = 0.0;
		}
		else if ( 0.0 == ecc )
		{
			aop = 0.0;
		}

		// semi-latus rectum
		double p { getSemilatusRectum( a, ecc ) };

		// radius in perifocal frame
		Vector3 RofBwrtCexpP { ZERO_VECTOR3 };
		RofBwrtCexpP[0] = p * cTheta / ( 1.0 + ecc * cTheta );
		RofBwrtCexpP[1] = p * sTheta / ( 1.0 + ecc * cTheta );

		// velocity in perifocal frame
		Vector3 VofBwrtIexpP { ZERO_VECTOR3 };
		double sqrtMuOP { std::sqrt( Earth::mu / p ) };
		VofBwrtIexpP[0] = -1.0 * sqrtMuOP * sTheta;
		VofBwrtIexpP[1] = sqrtMuOP * ( ecc + cTheta );

		// transform to ECI frame
		FrameTransform CfromPtoI;
		CfromPtoI.setP2I( inc, raan, aop );
		Vector3 RofBwrtCexpI = CfromPtoI.getDCM() * RofBwrtCexpP;
		Vector3 VofBwrtIexpI = CfromPtoI.getDCM() * VofBwrtIexpP;

		return Vector6 { RofBwrtCexpI[0],
						 RofBwrtCexpI[1],
						 RofBwrtCexpI[2],
						 VofBwrtIexpI[0],
						 VofBwrtIexpI[1],
						 VofBwrtIexpI[2] };
	}

	// (overload) conversion keplerian orbial elements to ECI position and velocity
	inline const Vector6 kepoe2I(const Vector6& state)
	{
		return kepoe2I( state[0], state[1], state[2], state[3], state[4], state[5] );
	}

	// geocentric latitude given ECEF position
	inline const double getGeocentricLatitude(const Vector3& RofBwrtCexpE)
	{
		return std::asin( RofBwrtCexpE[2] / RofBwrtCexpE.mag() );
	}

	// (overload) geocentric latitude given ECEF position and magnitude
	inline const double getGeocentricLatitude(const Vector3& RofBwrtCexpE, const double& RofBwrtCmag)
	{
		return std::asin( RofBwrtCexpE[2] / RofBwrtCmag );
	}

	// (overload) geocentric latitude given geodetic latitude
	inline const double getGeocentricLatitude(const double& gdLat)
	{
		return std::atan( ( 1.0 - Earth::eccentricity * Earth::eccentricity ) * std::tan( gdLat ) );
	}

	// geodetic latitude given geocentric latitude
	inline const double getGeodeticLatitude(const double& gcLat)
	{
		return std::atan( std::tan( gcLat ) / ( 1.0 - Earth::eccentricity * Earth::eccentricity ) );
	}

	// (overload) geodetic latitude given ECEF position
	inline const double getGeodeticLatitude(const Vector3& RofBwrtCexpE)
	{
		return getGeodeticLatitude( getGeocentricLatitude( RofBwrtCexpE ) );
	}

	// longitude given ECEF position
	inline const double getLongitude(const Vector3& RofBwrtCexpE)
	{
		return std::atan2( RofBwrtCexpE[1], RofBwrtCexpE[0] );
	}

	// altitude given ECEF position
	inline const double getAltitude(const Vector3& RofBwrtCexpE)
	{
		double p { std::sqrt( RofBwrtCexpE[0] * RofBwrtCexpE[0] + RofBwrtCexpE[1] * RofBwrtCexpE[1] ) }; 
		double gdLat { getGeodeticLatitude( RofBwrtCexpE ) };
		return (
			p * std::cos( gdLat ) + RofBwrtCexpE[2] * std::sin( gdLat ) - Earth::radius 
			* std::sqrt( 1.0 - Earth::eccentricity * Earth::eccentricity * std::sin( gdLat ) * std::sin( gdLat ) )
		);
	}

	// (overload) altitude given ECEF position and geocetric latitude
	inline const double getAltitude(const Vector3& RofBwrtCexpE, const double& gdLat)
	{
		double p { std::sqrt( RofBwrtCexpE[0] * RofBwrtCexpE[0] + RofBwrtCexpE[1] * RofBwrtCexpE[1] ) }; 
		return (
			p * std::cos( gdLat ) + RofBwrtCexpE[2] * std::sin( gdLat ) - Earth::radius 
			* std::sqrt( 1.0 - Earth::eccentricity * Earth::eccentricity * std::sin( gdLat ) * std::sin( gdLat ) )
		);
	}

	// right ascension given ECI position
	inline const double getRightAscension(const Vector3& RofBwrtCexpI)
	{
		return std::atan2( RofBwrtCexpI[1], RofBwrtCexpI[0] );
	}

	// sidereal time given ECI position
	inline const double getSiderealTime(const Vector3& RofBwrtCexpI)
	{
		return std::atan2( RofBwrtCexpI[1], RofBwrtCexpI[0] );
	}
};

#endif  // COORDINATETRANSFORM_HH
