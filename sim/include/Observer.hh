/*
** ------------ Header Guard -------------
*/ 
#ifndef OBSERVER_HH  
#define OBSERVER_HH

/*
** ------- Preprocessor directives -------
*/ 
#include "Model.hh"
#include "Vector.hh"
#include "Spacecraft.hh"
#include "InputParser.hh"
#include <string>	// for std::string
#include <cstddef>  // for std::size_t

/*
** -------------- Constants ---------------
*/ 
inline constexpr int MAX_SPACECRAFT_TO_TRACK { 64 };	// max number of spacecraft available to track

/*
** -------- Forward Declarations ----------
*/ 
class Earth;

/*
** --------- Namespace directives ---------
*/ 

/*
** ----------- Class Definition ------------
*/ 
class Observer : public Model
{
	Earth* _pEarth { nullptr };
	Spacecraft* _pSpacecraftArray[MAX_SPACECRAFT_TO_TRACK] { nullptr };
	std::size_t _numSpacecraft { 0 };

public:

	// ECI states
	Vector3 RwrtOexpN { ZERO_VECTOR3 };
	Vector3 VwrtNexpN { ZERO_VECTOR3 };

	// ECEF states
	Vector3 RwrtOexpE { ZERO_VECTOR3 };
	Vector3 VwrtEexpE { ZERO_VECTOR3 };

	// NED states
	FrameTransform CfromNtoD;
	Vector3 RwrtOexpD { ZERO_VECTOR3 };
	Vector3 VwrtNexpD { ZERO_VECTOR3 };

	// Tropocentric states
	FrameTransform CfromNtoT;
	Vector3 RwrtOexpT { ZERO_VECTOR3 };
	Vector3 VwrtNexpT { ZERO_VECTOR3 };

	double gcLat  	{ 0.0 };	// geocentric latitude [rad]
	double gdLat    { 0.0 };  	// geodetic latitude [rad]
	double lon		{ 0.0 };	// longitude [rad]
	double alt 		{ 0.0 };	// altitude above geoid [km]
	double st		{ 0.0 };	// sidereal time [rad]

	Vector3 RwrtSexpNArray[MAX_SPACECRAFT_TO_TRACK] { ZERO_VECTOR3 };	// range wrt ECI array [km]
	Vector3 RwrtSexpEArray[MAX_SPACECRAFT_TO_TRACK] { ZERO_VECTOR3 };	// range wrt ECEF array [km]
	Vector3 RwrtSexpDArray[MAX_SPACECRAFT_TO_TRACK] { ZERO_VECTOR3 };	// range wrt NED array [km]
	Vector3 RwrtSexpTArray[MAX_SPACECRAFT_TO_TRACK] { ZERO_VECTOR3 };	// range wrt Topocentric array [km]
	double azArray[MAX_SPACECRAFT_TO_TRACK] { 0.0 };  		// azimuth array [rad] (measured cw from North)
	double elArray[MAX_SPACECRAFT_TO_TRACK] { 0.0 };		// elevation array [rad]
	double raArray[MAX_SPACECRAFT_TO_TRACK] { 0.0 };  		// right ascension array [rad] (measured cw from North)
	double declArray[MAX_SPACECRAFT_TO_TRACK] { 0.0 };		// declination array [rad]

	// default constructor (disabled)
	Observer() = delete;

	// parameterized constructor
	Observer(const std::string& name, json inputFileData, Earth* pEarth);

	// destructor
	~Observer() = default;

	// forward declarations
	virtual void initModel() override;
	virtual void updateDerivs() override;
	virtual void updateStateDependents() override;

	void registerSpacecraft(Spacecraft* pSpacecraft);

	// access functions

	// setter functions

};

#endif  // OBSERVER_HH
