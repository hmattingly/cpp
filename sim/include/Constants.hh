// ------- Header Guard -------
#ifndef CONSTANTS_HH  
#define CONSTANTS_HH

// ------- Preprocessor directives -------
#include <limits>			// for max double and int

#define MIN(x, y) 	((x) < (y) ? (x) : (y))
#define MAX(x, y) 	((x) > (y) ? (x) : (y))
#define ABS(x) 		((x) < 0.0 ? (-1.0 * (x)) : (x))

// ------- Namespace directives -------
namespace Constants
{	
	// universal constants
	inline constexpr double PI 		{ 3.141592653589793116 };	// Pi
	inline constexpr double TWO_PI 	{ 2.0 * PI };				// 2*Pi
	inline constexpr double G 		{ 6.67430e-20 };			// gravitational constant [km^3/kg/s^2]
	inline constexpr double c 		{ 299'792.457999 };			// speed of light [km/s]

	// angle conversions
	inline constexpr double RAD2DEG    { 180.0 / PI };			// radians to degrees
	inline constexpr double DEG2RAD    { 1.0 / RAD2DEG };		// degrees to radians
	inline constexpr double DEG2ARCMIN { 60.0 };				// degrees to arcminutes
	inline constexpr double ARCMIN2DEG { 1.0 / DEG2ARCMIN };	// arcminutes to degrees
	inline constexpr double ARCMIN2RAD { ARCMIN2DEG * DEG2RAD };// arcminutes to radians
	inline constexpr double RAD2ARCMIN { RAD2DEG * DEG2ARCMIN };// radians to arcminutes
	inline constexpr double DEG2ARCSEC { 3600.0 };				// degrees to arcseconds
	inline constexpr double ARCSEC2DEG { 1.0 / DEG2ARCSEC };	// arcseconds to degrees
	inline constexpr double ARCSEC2RAD { ARCSEC2DEG * DEG2RAD };// arcseconds to radians
	inline constexpr double RAD2ARCSEC { RAD2DEG * DEG2ARCSEC };// radians to arcseconds

	// length conversions
	inline constexpr double KM2M  { 1000.0 };			// kilometers to meters
	inline constexpr double M2KM  { 1.0 / KM2M };		// meters to kilometers
	inline constexpr double AU2KM { 149'597'870.7 };	// astronomical unit to kilometers
	inline constexpr double KM2AU { 1.0 / AU2KM };		// kilometers to astronomical unit

	// time conversions
	inline constexpr double SOLAR_DAY 		{ 86'400.0 };			// solar day [s]
	inline constexpr double SIDEREAL_DAY 	{ 86'164.09053083288 };	// mean sidereal day [s]

	// C++ constants
	inline constexpr double FLOAT_TOL 	{ 1e-12 };	// tolerance for floating point comparisons
	inline constexpr double MAX_DOUBLE 	{ std::numeric_limits<double>::max() };	// max double value (~1.798e308)
	inline constexpr int MAX_INT 		{ std::numeric_limits<int>::max() };

}


#endif  // CONSTANTS_HH
