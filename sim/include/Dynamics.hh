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
struct SpacecraftBody;

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
	virtual void calcAwrtOexpN() = 0;

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
	void calcAwrtOexpN() override;

	// access functions

	// setter functions
};


#endif  // DYNAMICS_HH
