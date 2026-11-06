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
#include <string>	// for std::string

/*
** -------------- Constants ---------------
*/ 

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

public:
	Vector3 RwrtOexpN { ZERO_VECTOR3 };
	Vector3 RwrtOexpE { ZERO_VECTOR3 };
	Vector3 VwrtEexpE { ZERO_VECTOR3 };

	double gcLat  	{ 0.0 };	// geocentric latitude
	double gdLat    { 0.0 };  	// geodetic latitude
	double lon		{ 0.0 };	// longitude
	double alt 		{ 0.0 };	// altitude above geoid
	double st		{ 0.0 };	// sidereal time

	// default constructor (disabled)
	Observer() = delete;

	// parameterized constructor
	Observer(const std::string& name);

	// destructor
	~Observer() = default;

	// forward declarations
	virtual void initModel() override;
	virtual void updateDerivs() override;
	virtual void updateStateDependents() override;

	// access functions

	// setter functions

};

#endif  // OBSERVER_HH
