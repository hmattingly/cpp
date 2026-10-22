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
	SpacecraftBody& _body;

public:
	// default constructor
	Dynamics() = delete;

	// parameterized constructor
	Dynamics(SpacecraftBody& body);

	// destructor
	virtual ~Dynamics() = default;

	// forward declarations
	virtual const Vector3 getAwrtOexpN() = 0;

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
	TwoBodyDynamics(SpacecraftBody& body);

	// destructor
	~TwoBodyDynamics() = default;

	// forward declarations
	const Vector3 getAwrtOexpN() override;

	// access functions

	// setter functions
};

/*
** ----------- Class Definition ------------
*/ 
class J2Dynamics : public Dynamics
{
	const double _J2;

public:
	// default constructor
	J2Dynamics() = delete;

	// parameterized constructor
	J2Dynamics(SpacecraftBody& body);

	// destructor
	~J2Dynamics() = default;

	// forward declarations
	const Vector3 getAwrtOexpN() override;

	// access functions

	// setter functions
};

/*
** ----------- Class Definition ------------
*/ 
class J3Dynamics : public Dynamics
{
	const double _J3;

public:
	// default constructor
	J3Dynamics() = delete;

	// parameterized constructor
	J3Dynamics(SpacecraftBody& body);

	// destructor
	~J3Dynamics() = default;

	// forward declarations
	const Vector3 getAwrtOexpN() override;

	// access functions

	// setter functions
};

/*
** ----------- Class Definition ------------
*/ 
class J4Dynamics : public Dynamics
{
	const double _J4;

public:
	// default constructor
	J4Dynamics() = delete;

	// parameterized constructor
	J4Dynamics(SpacecraftBody& body);

	// destructor
	~J4Dynamics() = default;

	// forward declarations
	const Vector3 getAwrtOexpN() override;

	// access functions

	// setter functions
};

#endif  // DYNAMICS_HH
