/*
** ------------ Header Guard -------------
*/ 
#ifndef CELESTIALBODY_HH  
#define CELESTIALBODY_HH

/*
** ------- Preprocessor directives -------
*/ 
#include "Vector.hh"
#include "Matrix.hh"
#include "Model.hh"
#include "Constants.hh"
#include <string>			// for std::string

/*
** -------------- Constants ---------------
*/ 

/*
** -------- Forward Declarations ----------
*/ 
class Epoch;

/*
** --------- Namespace directives ---------
*/ 
namespace EarthOrientation
{
    inline constexpr std::size_t NUTATION_ROW_COUNT { 106 };
    inline constexpr std::size_t NUTATION_COL_COUNT { 9 };

    using NutationTable =
        Matrix<NUTATION_ROW_COUNT, NUTATION_COL_COUNT>;

    inline const NutationTable NUTATION_COEFF {
        {  0,  0,  0,  0, 1, -171996.0, -174.2,  92025.0,  8.9 },
        {  0,  0,  0,  0, 2,    2062.0,    0.2,   -895.0,  0.5 },
        { -2,  0,  2,  0, 1,      46.0,    0.0,    -24.0,  0.0 },
        {  2,  0, -2,  0, 0,      11.0,    0.0,      0.0,  0.0 },
        { -2,  0,  2,  0, 2,      -3.0,    0.0,      1.0,  0.0 },
        {  1, -1,  0, -1, 0,      -3.0,    0.0,      0.0,  0.0 },
        {  0, -2,  2, -2, 1,      -2.0,    0.0,      1.0,  0.0 },
        {  2,  0, -2,  0, 1,       1.0,    0.0,      0.0,  0.0 },
        {  0,  0,  2, -2, 2,  -13187.0,   -1.6,   5736.0, -3.1 },
        {  0,  1,  0,  0, 0,    1426.0,   -3.4,     54.0, -0.1 },
        {  0,  1,  2, -2, 2,    -517.0,    1.2,    224.0, -0.6 },
        {  0, -1,  2, -2, 2,     217.0,   -0.5,    -95.0,  0.3 },
        {  0,  0,  2, -2, 1,     129.0,    0.1,    -70.0,  0.0 },
        {  2,  0,  0, -2, 0,      48.0,    0.0,      1.0,  0.0 },
        {  0,  0,  2, -2, 0,     -22.0,    0.0,      0.0,  0.0 },
        {  0,  2,  0,  0, 0,      17.0,   -0.1,      0.0,  0.0 },
        {  0,  1,  0,  0, 1,     -15.0,    0.0,      9.0,  0.0 },
        {  0,  2,  2, -2, 2,     -16.0,    0.1,      7.0,  0.0 },
        {  0, -1,  0,  0, 1,     -12.0,    0.0,      6.0,  0.0 },
        { -2,  0,  0,  2, 1,      -6.0,    0.0,      3.0,  0.0 },
        {  0, -1,  2, -2, 1,      -5.0,    0.0,      3.0,  0.0 },
        {  2,  0,  0, -2, 1,       4.0,    0.0,     -2.0,  0.0 },
        {  0,  1,  2, -2, 1,       4.0,    0.0,     -2.0,  0.0 },
        {  1,  0,  0, -1, 0,      -4.0,    0.0,      0.0,  0.0 },
        {  2,  1,  0, -2, 0,       1.0,    0.0,      0.0,  0.0 },
        {  0,  0, -2,  2, 1,       1.0,    0.0,      0.0,  0.0 },
        {  0,  1, -2,  2, 0,      -1.0,    0.0,      0.0,  0.0 },
        {  0,  1,  0,  0, 2,       1.0,    0.0,      0.0,  0.0 },
        { -1,  0,  0,  1, 1,       1.0,    0.0,      0.0,  0.0 },
        {  0,  1,  2, -2, 0,      -1.0,    0.0,      0.0,  0.0 },
        {  0,  0,  2,  0, 2,   -2274.0,   -0.2,    977.0, -0.5 },
        {  1,  0,  0,  0, 0,     712.0,    0.1,     -7.0,  0.0 },
        {  0,  0,  2,  0, 1,    -386.0,   -0.4,    200.0,  0.0 },
        {  1,  0,  2,  0, 2,    -301.0,    0.0,    129.0, -0.1 },
        {  1,  0,  0, -2, 0,    -158.0,    0.0,     -1.0,  0.0 },
        { -1,  0,  2,  0, 2,     123.0,    0.0,    -53.0,  0.0 },
        {  0,  0,  0,  2, 0,      63.0,    0.0,     -2.0,  0.0 },
        {  1,  0,  0,  0, 1,      63.0,    0.1,    -33.0,  0.0 },
        { -1,  0,  0,  0, 1,     -58.0,   -0.1,     32.0,  0.0 },
        { -1,  0,  2,  2, 2,     -59.0,    0.0,     26.0,  0.0 },
        {  1,  0,  2,  0, 1,     -51.0,    0.0,     27.0,  0.0 },
        {  0,  0,  2,  2, 2,     -38.0,    0.0,     16.0,  0.0 },
        {  2,  0,  0,  0, 0,      29.0,    0.0,     -1.0,  0.0 },
        {  1,  0,  2, -2, 2,      29.0,    0.0,    -12.0,  0.0 },
        {  2,  0,  2,  0, 2,     -31.0,    0.0,     13.0,  0.0 },
        {  0,  0,  2,  0, 0,      26.0,    0.0,     -1.0,  0.0 },
        { -1,  0,  2,  0, 1,      21.0,    0.0,    -10.0,  0.0 },
        { -1,  0,  0,  2, 1,      16.0,    0.0,     -8.0,  0.0 },
        {  1,  0,  0, -2, 1,     -13.0,    0.0,      7.0,  0.0 },
        { -1,  0,  2,  2, 1,     -10.0,    0.0,      5.0,  0.0 },
        {  1,  1,  0, -2, 0,      -7.0,    0.0,      0.0,  0.0 },
        {  0,  1,  2,  0, 2,       7.0,    0.0,     -3.0,  0.0 },
        {  0, -1,  2,  0, 2,      -7.0,    0.0,      3.0,  0.0 },
        {  1,  0,  2,  2, 2,      -8.0,    0.0,      3.0,  0.0 },
        {  1,  0,  0,  2, 0,       6.0,    0.0,      0.0,  0.0 },
        {  2,  0,  2, -2, 2,       6.0,    0.0,     -3.0,  0.0 },
        {  0,  0,  0,  2, 1,      -6.0,    0.0,      3.0,  0.0 },
        {  0,  0,  2,  2, 1,      -7.0,    0.0,      3.0,  0.0 },
        {  1,  0,  2, -2, 1,       6.0,    0.0,     -3.0,  0.0 },
        {  0,  0,  0, -2, 1,      -5.0,    0.0,      3.0,  0.0 },
        {  1, -1,  0,  0, 0,       5.0,    0.0,      0.0,  0.0 },
        {  2,  0,  2,  0, 1,      -5.0,    0.0,      3.0,  0.0 },
        {  0,  1,  0, -2, 0,      -4.0,    0.0,      0.0,  0.0 },
        {  1,  0, -2,  0, 0,       4.0,    0.0,      0.0,  0.0 },
        {  0,  0,  0,  1, 0,      -4.0,    0.0,      0.0,  0.0 },
        {  1,  1,  0,  0, 0,      -3.0,    0.0,      0.0,  0.0 },
        {  1,  0,  2,  0, 0,       3.0,    0.0,      0.0,  0.0 },
        {  1, -1,  2,  0, 2,      -3.0,    0.0,      1.0,  0.0 },
        { -1, -1,  2,  2, 2,      -3.0,    0.0,      1.0,  0.0 },
        { -2,  0,  0,  0, 1,      -2.0,    0.0,      1.0,  0.0 },
        {  3,  0,  2,  0, 2,      -3.0,    0.0,      1.0,  0.0 },
        {  0, -1,  2,  2, 2,      -3.0,    0.0,      1.0,  0.0 },
        {  1,  1,  2,  0, 2,       2.0,    0.0,     -1.0,  0.0 },
        { -1,  0,  2, -2, 1,      -2.0,    0.0,      1.0,  0.0 },
        {  2,  0,  0,  0, 1,       2.0,    0.0,     -1.0,  0.0 },
        {  1,  0,  0,  0, 2,      -2.0,    0.0,      1.0,  0.0 },
        {  3,  0,  0,  0, 0,       2.0,    0.0,      0.0,  0.0 },
        {  0,  0,  2,  1, 2,       2.0,    0.0,     -1.0,  0.0 },
        { -1,  0,  0,  0, 2,       1.0,    0.0,     -1.0,  0.0 },
        {  1,  0,  0, -4, 0,      -1.0,    0.0,      0.0,  0.0 },
        { -2,  0,  2,  2, 2,       1.0,    0.0,     -1.0,  0.0 },
        { -1,  0,  2,  4, 2,      -2.0,    0.0,      1.0,  0.0 },
        {  2,  0,  0, -4, 0,      -1.0,    0.0,      0.0,  0.0 },
        {  1,  1,  2, -2, 2,       1.0,    0.0,     -1.0,  0.0 },
        {  1,  0,  2,  2, 1,      -1.0,    0.0,      1.0,  0.0 },
        { -2,  0,  2,  4, 2,      -1.0,    0.0,      1.0,  0.0 },
        { -1,  0,  4,  0, 2,       1.0,    0.0,      0.0,  0.0 },
        {  1, -1,  0, -2, 0,       1.0,    0.0,      0.0,  0.0 },
        {  2,  0,  2, -2, 1,       1.0,    0.0,     -1.0,  0.0 },
        {  2,  0,  2,  2, 2,      -1.0,    0.0,      0.0,  0.0 },
        {  1,  0,  0,  2, 1,      -1.0,    0.0,      0.0,  0.0 },
        {  0,  0,  4, -2, 2,       1.0,    0.0,      0.0,  0.0 },
        {  3,  0,  2, -2, 2,       1.0,    0.0,      0.0,  0.0 },
        {  1,  0,  2, -2, 0,      -1.0,    0.0,      0.0,  0.0 },
        {  0,  1,  2,  0, 1,       1.0,    0.0,      0.0,  0.0 },
        { -1, -1,  0,  2, 1,       1.0,    0.0,      0.0,  0.0 },
        {  0,  0, -2,  0, 1,      -1.0,    0.0,      0.0,  0.0 },
        {  0,  0,  2, -1, 2,      -1.0,    0.0,      0.0,  0.0 },
        {  0,  1,  0,  2, 0,      -1.0,    0.0,      0.0,  0.0 },
        {  1,  0, -2, -2, 0,      -1.0,    0.0,      0.0,  0.0 },
        {  0, -1,  2,  0, 1,      -1.0,    0.0,      0.0,  0.0 },
        {  1,  1,  0, -2, 1,      -1.0,    0.0,      0.0,  0.0 },
        {  1,  0, -2,  2, 0,      -1.0,    0.0,      0.0,  0.0 },
        {  2,  0,  0,  2, 0,       1.0,    0.0,      0.0,  0.0 },
        {  0,  0,  2,  4, 2,      -1.0,    0.0,      0.0,  0.0 },
        {  0,  1,  0,  1, 0,       1.0,    0.0,      0.0,  0.0 }
    };
}

namespace EarthAtmosphere
{
	inline constexpr std::size_t DENSLOOKUP_ROW_COUNT { 28 };
    inline constexpr std::size_t DENSLOOKUP_COL_COUNT { 4 };

    using DensityLookupTable =
        Matrix<DENSLOOKUP_ROW_COUNT, DENSLOOKUP_COL_COUNT>;

	inline const DensityLookupTable DENS_LOOKUP {
		// altitude (km), ref density (kg/m^3), ref altitude (km), scale height (km)
		{ 0, 	1.225, 		0, 		7.249 },
		{ 25, 	3.899e-2, 	25, 	6.349 },
		{ 30, 	1.774e-2, 	30, 	6.682 },
		{ 40, 	3.972e-3, 	40, 	7.554 },
		{ 50, 	1.057e-3, 	50, 	8.382 },
		{ 60, 	3.206e-4, 	60, 	7.714 },
		{ 70, 	8.770e-5, 	70, 	6.549 },
		{ 80, 	1.905e-5, 	80, 	5.799 },
		{ 90, 	3.396e-6, 	90, 	5.382 },
		{ 100, 	5.297e-7, 	100, 	5.877 },
		{ 110, 	5.877e-8, 	110, 	7.263 },
		{ 120, 	2.438e-8, 	120, 	9.473 },
		{ 130, 	8.484e-9, 	130, 	12.636 },
		{ 140, 	3.845e-9, 	140, 	16.149 },
		{ 150, 	2.070e-9, 	150,	22.523 },
		{ 180, 	5.464e-10, 	180, 	29.740 },
		{ 200, 	2.789e-10, 	200, 	37.105 },
		{ 250, 	7.248e-11, 	250, 	45.546 },
		{ 300, 	2.418e-11, 	300, 	53.628 },
		{ 350, 	9.518e-12, 	350, 	53.298 },
		{ 400, 	3.725e-12, 	400, 	58.515 },
		{ 450, 	1.585e-12, 	450, 	60.828 },
		{ 500, 	6.967e-13, 	500, 	63.822 },
		{ 600, 	1.454e-13, 	600, 	71.835 },
		{ 700, 	3.614e-14, 	700, 	88.667 },
		{ 800, 	1.170e-14, 	800, 	124.640 },
		{ 900, 	5.245e-15, 	900, 	181.050 },
		{ 1000, 3.019e-15, 	1000,	268.000 }
	};
}

/*
** ----------- Class Definition ------------
*/ 
class Earth : public Model
{
	Epoch* _pEpoch { nullptr };

	double _gmst { 0.0 };						// Greenwich mean sidereal time in rad
	double _gast { 0.0 };						// Greenwich apparent sidereal time in rad
	double _trueEpsilon { .409092804028403 };	// true obliquity of the ecliptic in rad (initialized to J2000)
	double _meanEpsilon { .409092804028403 }; 	// mean obliquity of the ecliptic in rad (initialized to J2000)
	double _xp { 2.102636934972058e-07 };		// polar motion x in rad (initialized to J2000)
	double _yp { 1.831747290652104e-06 };		// polar motion y in rad (initialized to J2000)
	double _dPsi { -6.750247617532480e-05 };	// nutation of longitude in rad (initialized to J2000)
	Matrix3 _PI { IDENTITY_MATRIX3 };			// polar motion DCM
	Matrix3 _TH { IDENTITY_MATRIX3 };			// Greenwich DCM
	Matrix3 _NU { IDENTITY_MATRIX3 };			// nutation DCM
	Matrix3 _PR { IDENTITY_MATRIX3 };			// precession DCM

public:
	static inline const std::string name { "Earth" };						// name of body
	static inline const double mu { 5.972168489579432e+24 * Constants::G };	// gravitational parameter in km^3/s^2
	static inline const double radius { 6378.1363 };						// mean equatorial radius in km
	static inline const double J2 { .001082626174 };						// J2 harmonic coefficient (unitless)
	static inline const double J3 { -.000002532411 };						// J3 harmonic coefficient (unitless)
	static inline const double J4 { -.000001619897 };						// J4 harmonic coefficient (unitless)
	static inline const double eccentricity { .081919084262 };			// geometric eccentricity (unitless)
	static inline const Vector3 omega { {0.0, 0.0, .00007292115} };		// rotation rate in rad/s
	static inline const EarthOrientation::NutationTable& nutationCoeff { EarthOrientation::NUTATION_COEFF };	// IAU 1980 nutation coefficients
	static inline const EarthAtmosphere::DensityLookupTable& densityLookup { EarthAtmosphere::DENS_LOOKUP };	// exponential atmospheric model (Table 8-4 of Vallado)

	// default constructor
	Earth();

	// destructor
	~Earth() = default;

	// forward declarations
	virtual void initModel() override;
	virtual void updateDerivs() override;
	virtual void updateStateDependents() override;
	static const double getDensity(const double& alt);
	static const double getGeoidHeight(const double& geocentricLat);
	void calcPolarMotion();
	void calcNutation();
	void calcPrecession();
	void calcEarthRotation();

	// access functions
	const double& getGMST() const { return _gmst; }
	const double& getGAST() const { return _gast; }
	const double& getTrueEpsilon() const { return _trueEpsilon; }
	const double& getMeanEpsilon() const { return _meanEpsilon; }
	const double& getXp() const { return _xp; }
	const double& getYp() const { return _yp; }
	const double& getDPsi() const { return _dPsi; }
	const Matrix3& getPolarMotionDCM() const { return _PI; }
	const Matrix3& getEarthRotationDCM() const { return _TH; }
	const Matrix3& getNutationDCM() const { return _NU; }
	const Matrix3& getPrecessionDCM() const { return _PR; }

	// setter functions
	void setXp(const double xp) { _xp = xp; }
	void setYp(const double yp) { _yp = yp; }

};

/*
** ----------- Class Definition ------------
*/ 
class Moon
{
public:
	static inline const std::string name { "Moon" };						// name of body
	static inline const double mu { 7.345789943736122e+22 * Constants::G };	// gravitational parameter in km^3/s^2
	static inline const double radius { 1737.4 };							// mean equatorial radius in km

	// default constructor
	Moon() = default;

	// destructor
	~Moon() = default;

	// forward declarations

	// access functions

	// setter functions

};

/*
** ----------- Class Definition ------------
*/ 
class Sun
{
public:
	static inline const std::string name { "Sun" };							// name of body
	static inline const double mu { 1.988409870967592e+30 * Constants::G };	// gravitational parameter in km^3/s^2
	static inline const double radius { 695'700 };							// mean equatorial radius in km

	// default constructor
	Sun() = default;

	// destructor
	~Sun() = default;

	// forward declarations

	// access functions

	// setter functions

};

#endif  // CELESTIALBODY_HH
