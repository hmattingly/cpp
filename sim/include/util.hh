// ------- Header Guard -------
#ifndef UTIL_HH  
#define UTIL_HH
 
#include "Vector.hh"		// for Vector3
#include "CelestialBody.hh"	// for CelestialBody
#include <iostream>
#include <string_view>
#include <numbers>			// for pi
#include <optional>			// for std::optional<>


namespace Util
{	
	// universal constants
	inline constexpr double PI { std::numbers::pi };	// Pi
	inline constexpr double G { 6.67430e-20 };			// gravitational constant in km^3/kg/s^2
	inline constexpr double AU { 149'597'870.7 };		// astronomical unit in km
	inline constexpr double c { 299'792.457999 };		// speed of light in km/s


	// angle conversions
	inline constexpr double RAD2DEG { 180.0 / PI };		// radians to degrees
	inline constexpr double DEG2RAD { PI / 180.0 };		// degrees to radians
	inline constexpr double DEG2ARC { 3600.0 };			// degrees to arcseconds
	inline constexpr double ARC2DEG { 1.0 / 3600.0 };		// arcseconds to degrees
	inline constexpr double ARC2RAD { ARC2DEG * DEG2RAD };	// arcseconds to radians
	inline constexpr double RAD2ARC { RAD2DEG * DEG2ARC };	// radians to arcseconds

	// celestial bodies
	inline const CelestialBody EARTH 
	{
		std::string_view("Earth"),				// name
		5.972168489579432e+24,					// mass in kg
		6378.1363,								// radius in km
		.001082626174,							// J2 (unitless)
        -.000002532411,							// J3 (unitless)
        -.000001619897,							// J4 (unitless)
		.081919084262,							// eccentricity (unitless)
		.409092804028403,						// mean obliquity of the ecliptic in rad
		86164.0905308,							// sidereal day in seconds
        Vector3 {0, 0, .00007292115}			// rotation rate in rad/s
	};

	inline const CelestialBody MOON
	{
		std::string_view("Moon"),				// name	
		7.345789943736122e+22,					// mass in kg
		1737.4,									// radius in km
		std::nullopt,							// J2 (unitless)
		std::nullopt,							// J3 (unitless)
		std::nullopt,							// J4 (unitless)
		std::nullopt,							// eccentricity (unitless)
		std::nullopt,							// mean obliquity of the ecliptic in degrees
		std::nullopt,							// sidereal day in seconds
		std::nullopt							// rotation rate in rad/s
	};

	inline const CelestialBody SUN
	{
		std::string_view("Sun"),				// name
		1.988409870967592e+30,					// mass in kg
		695'700,								// radius in km
		std::nullopt,							// J2 (unitless)
		std::nullopt,							// J3 (unitless)
		std::nullopt,							// J4 (unitless)
		std::nullopt,							// eccentricity (unitless)
		std::nullopt,							// mean obliquity of the ecliptic in degrees
		std::nullopt,							// sidereal day in seconds
		std::nullopt							// rotation rate in rad/s
	};
}


#endif  // UTIL_HH
