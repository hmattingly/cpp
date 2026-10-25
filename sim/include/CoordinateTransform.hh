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
	// specific angular momentum (HwrtOexpN) vector given ECI position and velocity
	inline const Vector3 getSpecAngularMomentum(const Vector3& RwrtOexpN, const Vector3& VwrtOexpN)
	{
		return Vector3 { cross( RwrtOexpN, VwrtOexpN ) };
	}

	// line of nodes unit vector (NwrtOexpNhat) given ECI position and velocity
	inline const Vector3 getLineOfNodesUnit(const Vector3& RwrtOexpN, const Vector3& VwrtOexpN)
	{
		Vector3 HwrtOexpN { getSpecAngularMomentum( RwrtOexpN, VwrtOexpN ) };

		return Vector3 { cross( Z_UNIT_VECTOR3, HwrtOexpN ).unit() };
	}

	// (overload) line of nodes unit vector (NwrtOexpNhat) given specific angular momentum vector
	inline const Vector3 getLineOfNodesUnit(const Vector3& HwrtOexpN)
	{
		return Vector3 { cross( Z_UNIT_VECTOR3, HwrtOexpN ).unit() };
	}

	// eccentricity vector (EwrtOexpN) given ECI position and velocity
	inline const Vector3 getEccentricityVector(const Vector3& RwrtOexpN, const Vector3& VwrtOexpN)
	{
		double RwrtOexpNmag { RwrtOexpN.mag() };
		double VwrtOexpNmag { VwrtOexpN.mag() };

		return Vector3 {
			( ( VwrtOexpNmag * VwrtOexpNmag - EARTH.mu / RwrtOexpNmag ) 
			* RwrtOexpN - dot( RwrtOexpN, VwrtOexpN ) * VwrtOexpN ) / EARTH.mu
		};
	}

	// eccentricity magnitude (ecc) given ECI position and velocity
	inline const double getEccentricity(const Vector3& RwrtOexpN, const Vector3& VwrtOexpN)
	{
		return getEccentricityVector( RwrtOexpN, VwrtOexpN ).mag();
	}

	// semimajor axis (a) given ECI position and velocity
	inline const double getSemimajorAxis(const Vector3& RwrtOexpN, const Vector3& VwrtOexpN)
	{
		double RwrtOexpNmag { RwrtOexpN.mag() };
		double VwrtOexpNmag { VwrtOexpN.mag() };
		double ecc { getEccentricity( RwrtOexpN, VwrtOexpN ) };

		if ( ABS( 1.0 - ecc ) < FLOAT_TOL )  // parabolic orbit
		{
			return MAX_DOUBLE;
		}
		else
		{
			return -1.0 * EARTH.mu * RwrtOexpNmag / ( VwrtOexpNmag * VwrtOexpNmag * RwrtOexpNmag - 2.0 * EARTH.mu );
		}
	}

	// (overload) semimajor axis (a) given ECI position and velocity magnitudes and eccentricity magnitude
	inline const double getSemimajorAxis(const double& RwrtOexpNmag, const double& VwrtOexpNmag, const double& ecc)
	{
		if ( ABS( 1.0 - ecc ) < FLOAT_TOL )  // parabolic orbit
		{
			return MAX_DOUBLE;
		}
		else
		{
			return -1.0 * EARTH.mu * RwrtOexpNmag / ( VwrtOexpNmag * VwrtOexpNmag * RwrtOexpNmag - 2.0 * EARTH.mu );
		}
	}

	// semiminor axis (b) given ECI position and velocity
	inline const double getSemiminorAxis(const Vector3& RwrtOexpN, const Vector3& VwrtOexpN)
	{
		double a { getSemimajorAxis( RwrtOexpN, VwrtOexpN ) };
		double ecc { getEccentricity( RwrtOexpN, VwrtOexpN ) };

		return a * std::sqrt( 1.0 - ecc * ecc );
	}

	// (overload) semimajor axis (b) given semimajor axis and eccentricity
	inline const double getSemiminorAxis(const double& a, const double& ecc)
	{
		return a * std::sqrt( 1.0 - ecc * ecc );
	}

	// semilatus rectum (p) given ECI position and velocity
	inline const double getSemilatusRectum(const Vector3& RwrtOexpN, const Vector3& VwrtOexpN)
	{
		double HwrtOexpNmag { getSpecAngularMomentum( RwrtOexpN, VwrtOexpN ).mag() };
		
		return HwrtOexpNmag * HwrtOexpNmag / EARTH.mu;
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
	const double getSemilatusRectum(const double& HwrtOexpNmag)
	{
		return HwrtOexpNmag * HwrtOexpNmag / EARTH.mu;
	}

	// apoapsis (Ra) given ECI position and velocity
	inline const double getApoapsis(const Vector3& RwrtOexpN, const Vector3& VwrtOexpN)
	{
		double a { getSemimajorAxis( RwrtOexpN, VwrtOexpN) };
		double ecc { getEccentricity( RwrtOexpN, VwrtOexpN ) };

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
	inline const double getPeriapsis(const Vector3& RwrtOexpN, const Vector3& VwrtOexpN)
	{
		double p { getSemilatusRectum(RwrtOexpN, VwrtOexpN) };
		double ecc { getEccentricity( RwrtOexpN, VwrtOexpN ) };

		return p / ( 1.0 + ecc );
	}

	// (overload) periapsis (Rp) given semilatus rectum and eccentricity magnitude
	inline const double getPeriapsis(const double& p, const double& ecc)
	{
		return p / ( 1.0 + ecc );
	}

	// mean motion (n) given ECI position and velocity
	inline const double getMeanMotion(const Vector3& RwrtOexpN, const Vector3& VwrtOexpN)
	{
		double a { getSemimajorAxis( RwrtOexpN, VwrtOexpN) };
		assert(a > 0.0);

		return std::sqrt( EARTH.mu / ( a * a * a ) );
	}

	// (overload) mean motion (n) given semimajor axis
	inline const double getMeanMotion(const double& a)
	{
		assert(a > 0.0);

		return std::sqrt( EARTH.mu / ( a * a * a ) );
	}

	// specific energy (energy) given ECI position and velocity
	const double getSpecEnergy(const Vector3& RwrtOexpN, const Vector3& VwrtOexpN)
	{
		return 0.5 * VwrtOexpN.mag2() - EARTH.mu / RwrtOexpN.mag();
	}

	// (overload) specific energy (energy) given semimajor axis
	inline const double getSpecEnergy(const double& a)
	{
		return -0.5 * EARTH.mu / a;
	}

	// inclination (inc) given ECI position and velocity
	inline const double getInclination(const Vector3& RwrtOexpN, const Vector3& VwrtOexpN)
	{
		Vector3 HwrtOexpNhat { getSpecAngularMomentum( RwrtOexpN, VwrtOexpN ).unit() };
		
		return std::acos( HwrtOexpNhat[2] );
	}

	// (overload) inclination (inc) given specific angular momentum unit vector
	inline const double getInclination(const Vector3& HwrtOexpNhat)
	{
		return std::acos( HwrtOexpNhat[2] );
	}

	// right ascension of the ascending node (raan) given ECI position and velocity
	inline const double getRightAscension(const Vector3& RwrtOexpN, const Vector3& VwrtOexpN)
	{
		double inc { getInclination( RwrtOexpN, VwrtOexpN ) };
		Vector3 NwrtOexpNhat { getLineOfNodesUnit( RwrtOexpN, VwrtOexpN ) };

		if ( ABS( inc ) < FLOAT_TOL ) // equatorial orbit
		{
			return 0.0;  // RAAN undefined
		}
		else 
		{
			if ( NwrtOexpNhat[1] < 0.0 )
			{
				return TWO_PI - std::acos( NwrtOexpNhat[0] );
			}
			else
			{
				return std::acos( NwrtOexpNhat[0] );
			}
		}
	}

	// (overload) right ascension of the ascending node (raan) given inclination and line of nodes unit vector
	inline const double getRightAscension(const double& inc, const Vector3& NwrtOexpNhat)
	{
		if ( ABS( inc ) < FLOAT_TOL ) // equatorial orbit
		{
			return 0.0;  // RAAN undefined
		}
		else 
		{
			if ( NwrtOexpNhat[1] < 0.0 )
			{
				return TWO_PI - std::acos( NwrtOexpNhat[0] );
			}
			else
			{
				return std::acos( NwrtOexpNhat[0] );
			}
		}
	}

	// argument of periapsis (aop) given ECI position and velocity
	inline const double getArgumentOfPeriapsis(const Vector3& RwrtOexpN, const Vector3& VwrtOexpN)
	{
		Vector3 NwrtOexpNhat { getLineOfNodesUnit( RwrtOexpN, VwrtOexpN ) };
		Vector3 EwrtOexpN { getEccentricityVector( RwrtOexpN, VwrtOexpN ) };
		double ecc { EwrtOexpN.mag() };
		double inc { getInclination( RwrtOexpN, VwrtOexpN ) };
		
		if ( ecc < FLOAT_TOL || ABS( inc ) < FLOAT_TOL )  // circular or equatorial orbit
		{
			return 0.0;  // AOP undefined
		}
		else
		{
			if ( EwrtOexpN[2] < 0.0 )
			{
				return TWO_PI - std::acos( dot( NwrtOexpNhat, EwrtOexpN / ecc ) );
			}
			else
			{
				return std::acos( dot( NwrtOexpNhat, EwrtOexpN / ecc ) );
			}
		}
	}

	// (overload) argument of periapsis (aop) given inclination, eccentricity vector, and line of nodes unit vector
	inline const double getArgumentOfPeriapsis(const double& inc, const Vector3& EwrtOexpN, const Vector3& NwrtOexpNhat)
	{
		double ecc { EwrtOexpN.mag() };
		
		if ( ecc < FLOAT_TOL || ABS( inc ) < FLOAT_TOL )  // circular or equatorial orbit
		{
			return 0.0;  // AOP undefined
		}
		else
		{
			if ( EwrtOexpN[2] < 0.0 )
			{
				return TWO_PI - std::acos( dot( NwrtOexpNhat, EwrtOexpN / ecc ) );
			}
			else
			{
				return std::acos( dot( NwrtOexpNhat, EwrtOexpN / ecc ) );
			}
		}
	}

	// true anomaly (ta) given ECI position and velocity, and inclination, eccentricity vector, and line of nodes unit vector (optional)
	inline const double getTrueAnomaly(const Vector3& RwrtOexpN, const Vector3& VwrtOexpN, double inc=0.0, Vector3 EwrtOexpN=ZERO_VECTOR3, Vector3 NwrtOexpNhat=ZERO_VECTOR3)
	{
		if ( 0.0 == inc )
		{
			inc = getInclination( RwrtOexpN, VwrtOexpN );
		}
		if ( ZERO_VECTOR3 == EwrtOexpN )
		{
			EwrtOexpN = getEccentricityVector( RwrtOexpN, VwrtOexpN );
		}
		if ( ZERO_VECTOR3 == NwrtOexpNhat )
		{
			NwrtOexpNhat = getLineOfNodesUnit( RwrtOexpN, VwrtOexpN );
		}
		
		double ecc { EwrtOexpN.mag() };
		double RwrtOexpNmag { RwrtOexpN.mag() };
		Vector3 RwrtOexpNhat { RwrtOexpN / RwrtOexpNmag };

		// return true longitude (ecc = 0 and inc = 0)
		if ( ecc < FLOAT_TOL && ABS( inc ) < FLOAT_TOL )
		{
			if ( RwrtOexpN[1] < 0.0 )
			{
				return TWO_PI - std::acos( RwrtOexpN[0] / RwrtOexpNmag );
			}
			else
			{
				return std::acos( RwrtOexpN[0] / RwrtOexpNmag );
			}
		}
		// return true longitude of periapsis (ecc != 0, inc = 0)
		else if ( ecc > FLOAT_TOL && ABS( inc ) < FLOAT_TOL )
		{
			if ( EwrtOexpN[1] < 0.0 )
			{
				return TWO_PI - std::acos( EwrtOexpN[0] / ecc );
			}
			else
			{
				return std::acos( EwrtOexpN[0] / ecc );
			}
		}
		// return argument of latitude (ecc = 0, inc != 0)
		else if ( ecc < FLOAT_TOL && ABS( inc ) >= FLOAT_TOL )
		{
			if ( RwrtOexpN[2] < 0.0 )
			{
				return TWO_PI - std::acos( dot( NwrtOexpNhat, RwrtOexpNhat ) );
			}
			else
			{
				return std::acos( dot( NwrtOexpNhat, RwrtOexpNhat ) );
			}
		}
		// return true anomaly
		else 
		{
			// prevent numerical errors near TA = 0
			double EdotR { dot( EwrtOexpN / ecc, RwrtOexpNhat ) };
			EdotR = MAX( -1.0, MIN( 1.0, EdotR ) );

			if ( dot( RwrtOexpN, VwrtOexpN ) < 0.0 )
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
	inline const double getEccentricAnomaly(const Vector3& RwrtOexpN, const Vector3& VwrtOexpN)
	{
		double ta { getTrueAnomaly( RwrtOexpN, VwrtOexpN ) };
		double ecc { getEccentricity( RwrtOexpN, VwrtOexpN ) };

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
	inline const double getParabolicAnomaly(const Vector3& RwrtOexpN, const Vector3& VwrtOexpN)
	{
		double ta { getTrueAnomaly( RwrtOexpN, VwrtOexpN ) };
		double ecc { getEccentricity( RwrtOexpN, VwrtOexpN ) };

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
	inline const double getHyperbolicAnomaly(const Vector3& RwrtOexpN, const Vector3& VwrtOexpN)
	{
		double ta { getTrueAnomaly( RwrtOexpN, VwrtOexpN ) };
		double ecc { getEccentricity( RwrtOexpN, VwrtOexpN ) };

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
	inline const double getMeanAnomaly(const Vector3& RwrtOexpN, const Vector3& VwrtOexpN)
	{
		double E { getEccentricAnomaly( RwrtOexpN, VwrtOexpN ) };
		double ecc { getEccentricity( RwrtOexpN, VwrtOexpN ) };

		return E - ecc * std::sin( E );
	}

	// (overload) mean anomaly (M) given eccentricity magnitude and eccentric anomaly
	inline const double getMeanAnomaly(const double& ecc, const double& E)
	{
		return E - ecc * std::sin( E );
	}

	// flight path angle (fpa) given ECI position and velocity
	inline const double getFlightPathAngle(const Vector3& RwrtOexpN, const Vector3& VwrtOexpN)
	{
		double HwrtOexpNmag { getSpecAngularMomentum( RwrtOexpN, VwrtOexpN ).mag() };
		
		return std::atan2( dot( RwrtOexpN, VwrtOexpN), HwrtOexpNmag );
	}

	// orbital period (P) given ECI position and velocity
	inline const double getPeriod(const Vector3& RwrtOexpN, const Vector3& VwrtOexpN)
	{
		double n { getMeanMotion( RwrtOexpN, VwrtOexpN ) };
		assert(n > 0.0);
		
		return TWO_PI / n;
	}

	// orbital period (P) given mean motion
	inline const double getPeriod(const double& n)
	{
		return TWO_PI / n;
	}

	
	// conversion from ECI position and velocity to keplerian orbial elements
	inline const Vector6 N2kepoe(const Vector3& RwrtOexpN, const Vector3& VwrtOexpN)
	{	
		// specific angular momentum
		Vector3 HwrtOexpN { getSpecAngularMomentum( RwrtOexpN, VwrtOexpN ) };

		// line of nodes
		Vector3 NwrtOexpNhat { getLineOfNodesUnit( HwrtOexpN ) };

		// eccentricity
		Vector3 EwrtOexpN { getEccentricityVector( RwrtOexpN, VwrtOexpN ) };
		double ecc { EwrtOexpN.mag() };

		// semi-major axis
		double a { getSemimajorAxis( RwrtOexpN.mag(), VwrtOexpN.mag(), ecc ) };

		// inclination
		double inc { getInclination( HwrtOexpN.unit() ) };

		// right ascension of the ascending node
		double raan { getRightAscension( inc, NwrtOexpNhat) };

		// argument of periapsis
		double aop { getArgumentOfPeriapsis( inc, EwrtOexpN, NwrtOexpNhat) };

		// determine true longitude, argument of latitude, or true anomaly
		double theta { getTrueAnomaly( RwrtOexpN, VwrtOexpN, inc, EwrtOexpN, NwrtOexpNhat ) };

		return Vector6 { a,	ecc, inc, raan, aop, theta };
	}

	// conversion keplerian orbial elements to ECI position and velocity
	inline const Vector6 kepoe2N(double a, 
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
		Vector3 RwrtOexpP { ZERO_VECTOR3 };
		RwrtOexpP[0] = p * cTheta / ( 1.0 + ecc * cTheta );
		RwrtOexpP[1] = p * sTheta / ( 1.0 + ecc * cTheta );

		// velocity in perifocal frame
		Vector3 VwrtOexpP { ZERO_VECTOR3 };
		double sqrtMuOP { std::sqrt( EARTH.mu / p ) };
		VwrtOexpP[0] = -1.0 * sqrtMuOP * sTheta;
		VwrtOexpP[1] = sqrtMuOP * ( ecc + cTheta );

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

	// (overload) conversion keplerian orbial elements to ECI position and velocity
	inline const Vector6 kepoe2N(const Vector6& state)
	{
		return kepoe2N( state[0], state[1], state[2], state[3], state[4], state[5] );
	}
};

#endif  // COORDINATETRANSFORM_HH
