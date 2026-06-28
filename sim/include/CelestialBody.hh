// ------- Header Guard -------
#ifndef CELESTIALBODY_HH  
#define CELESTIALBODY_HH
 
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

#endif // CELESTIALBODY_HH
