// ------- Header Guard -------
#ifndef CELESTIALBODY_HH  
#define CELESTIALBODY_HH

// ------- Preprocessor directives -------
#include "Vector.hh"		// for Vector3
#include <string_view>		// for std::string_view
#include <optional>			// for std::optional<>

// ------- Struct Definition -------
struct CelestialBody
{
	std::string_view name;
	double mass;
	double radius;

	std::optional<double> J2;
	std::optional<double> J3;
	std::optional<double> J4;
	std::optional<double> eccentricity;
	std::optional<double> epsilon; 			// mean obliquity of the ecliptic
	std::optional<double> siderealDay;		// length of sidereal day in seconds
	std::optional<Vector3> omega;			// rotation rate

};

// ------- Namespace directives -------
namespace CelestialBodies
{
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

#endif // CELESTIALBODY_HH
