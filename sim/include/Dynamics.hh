/*
** ------------ Header Guard -------------
*/ 
#ifndef DYNAMICS_HH  
#define DYNAMICS_HH

/*
** ------- Preprocessor directives -------
*/ 
#include "Vector.hh"
#include "SpacecraftBody.hh"

/*
** -------------- Constants ---------------
*/ 
inline constexpr int MAX_DYNAMIC { 6 };	// max number dynamic options

/*
** -------- Forward Declarations ----------
*/ 


/*
** --------- Namespace directives ---------
*/ 
class Earth;

/*
** ---------- Struct Definition -----------
*/ 
struct DynamicsOptions {
    bool twoBody { false };
    bool j2 { false };
    bool j3 { false };
    bool j4 { false };
    bool srp { false };
    bool drag { false };
};

/*
** ----------- Class Definition ------------
*/ 
class Dynamics
{
protected:

	SpacecraftBody* _pBody;
	Earth* _pEarth;

public:
	// default constructor
	Dynamics() = delete;

	// parameterized constructor
	Dynamics(SpacecraftBody* pBody, Earth* pEarth);

	// destructor
	virtual ~Dynamics() = default;

	// forward declarations
	virtual const Vector3 getAwrtNexpN() = 0;

	// access functions

	// setter functions

};


/*
** ----------- Class Definition ------------
*/ 
class TwoBodyDynamics : public Dynamics
{

public:
	// default constructor
	TwoBodyDynamics() = delete;

	// parameterized constructor
	TwoBodyDynamics(SpacecraftBody* pBody, Earth* pEarth);

	// destructor
	~TwoBodyDynamics() = default;

	// forward declarations
	const Vector3 getAwrtNexpN() override;

	// access functions

	// setter functions
};

/*
** ----------- Class Definition ------------
*/ 
class J2Dynamics : public Dynamics
{
public:
	// default constructor
	J2Dynamics() = delete;

	// parameterized constructor
	J2Dynamics(SpacecraftBody* pBody, Earth* pEarth);

	// destructor
	~J2Dynamics() = default;

	// forward declarations
	const Vector3 getAwrtNexpN() override;

	// access functions

	// setter functions
};

/*
** ----------- Class Definition ------------
*/ 
class J3Dynamics : public Dynamics
{

public:
	// default constructor
	J3Dynamics() = delete;

	// parameterized constructor
	J3Dynamics(SpacecraftBody* pBody, Earth* pEarth);

	// destructor
	~J3Dynamics() = default;

	// forward declarations
	const Vector3 getAwrtNexpN() override;

	// access functions

	// setter functions
};

/*
** ----------- Class Definition ------------
*/ 
class J4Dynamics : public Dynamics
{

public:
	// default constructor
	J4Dynamics() = delete;

	// parameterized constructor
	J4Dynamics(SpacecraftBody* pBody, Earth* pEarth);

	// destructor
	~J4Dynamics() = default;

	// forward declarations
	const Vector3 getAwrtNexpN() override;

	// access functions

	// setter functions
};

/*
** ----------- Class Definition ------------
*/ 
class DragDynamics : public Dynamics
{
	double _rho { 0.0 };  // atmospheric density [kg/m^3]
	
public:
	// default constructor
	DragDynamics() = delete;

	// parameterized constructor
	DragDynamics(SpacecraftBody* pBody, Earth* pEarth);

	// destructor
	~DragDynamics() = default;

	// forward declarations
	const Vector3 getAwrtNexpN() override;

	// access functions

	// setter functions
};

#endif  // DYNAMICS_HH
