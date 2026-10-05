// ------- Header Guard -------
#ifndef CONSTANTS_HH  
#define CONSTANTS_HH

// ------- Preprocessor directives -------
#include <numbers>			// for pi

// ------- Namespace directives -------
namespace Constants
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

	// C++ constants
	inline constexpr double FLOAT_TOL { 1e-12 };	// tolerance for floating point comparisons

}


#endif  // CONSTANTS_HH
