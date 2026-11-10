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
inline constexpr int MAX_DYNAMIC { 8 };	// max number dynamic options

/*
** -------- Forward Declarations ----------
*/ 


/*
** --------- Namespace directives ---------
*/ 
class Earth;
class Sun;
class Moon;

/*
** ---------- Struct Definition -----------
*/ 
struct DynamicsOptions {
    bool twoBody { false };
    bool j2 { false };
    bool j3 { false };
    bool j4 { false };
	bool sun { false };
	bool moon { false };
    bool srp { false };
    bool drag { false };
};

/*
** ----------- Class Definition ------------
*/ 
class Dynamics
{
protected:

	SpacecraftBody* _pBody { nullptr };

public:
	// default constructor
	Dynamics() = delete;

	// parameterized constructor
	Dynamics(SpacecraftBody* pBody);

	// destructor
	virtual ~Dynamics() = default;

	// forward declarations
	virtual const Vector3 getAofBwrtIexpI() = 0;

	// access functions

	// setter functions

};


/*
** ----------- Class Definition ------------
*/ 
class TwoBodyDynamics : public Dynamics
{
	Earth* _pEarth { nullptr };

public:
	// default constructor
	TwoBodyDynamics() = delete;

	// parameterized constructor
	TwoBodyDynamics(SpacecraftBody* pBody, Earth* pEarth);

	// destructor
	~TwoBodyDynamics() = default;

	// forward declarations
	const Vector3 getAofBwrtIexpI() override;

	// access functions

	// setter functions
};

/*
** ----------- Class Definition ------------
*/ 
class J2Dynamics : public Dynamics
{
	Earth* _pEarth { nullptr };

public:
	// default constructor
	J2Dynamics() = delete;

	// parameterized constructor
	J2Dynamics(SpacecraftBody* pBody, Earth* pEarth);

	// destructor
	~J2Dynamics() = default;

	// forward declarations
	const Vector3 getAofBwrtIexpI() override;

	// access functions

	// setter functions
};

/*
** ----------- Class Definition ------------
*/ 
class J3Dynamics : public Dynamics
{
	Earth* _pEarth { nullptr };

public:
	// default constructor
	J3Dynamics() = delete;

	// parameterized constructor
	J3Dynamics(SpacecraftBody* pBody, Earth* pEarth);

	// destructor
	~J3Dynamics() = default;

	// forward declarations
	const Vector3 getAofBwrtIexpI() override;

	// access functions

	// setter functions
};

/*
** ----------- Class Definition ------------
*/ 
class J4Dynamics : public Dynamics
{
	Earth* _pEarth { nullptr };

public:
	// default constructor
	J4Dynamics() = delete;

	// parameterized constructor
	J4Dynamics(SpacecraftBody* pBody, Earth* pEarth);

	// destructor
	~J4Dynamics() = default;

	// forward declarations
	const Vector3 getAofBwrtIexpI() override;

	// access functions

	// setter functions
};

/*
** ----------- Class Definition ------------
*/ 
class DragDynamics : public Dynamics
{
	Earth* _pEarth { nullptr };
	double _rho { 0.0 };  // atmospheric density [kg/m^3]
	
public:
	// default constructor
	DragDynamics() = delete;

	// parameterized constructor
	DragDynamics(SpacecraftBody* pBody, Earth* pEarth);

	// destructor
	~DragDynamics() = default;

	// forward declarations
	const Vector3 getAofBwrtIexpI() override;

	// access functions

	// setter functions
};

/*
** ----------- Class Definition ------------
*/ 
class SunDynamics : public Dynamics
{
	Sun* _pSun { nullptr };
	
public:
	// default constructor
	SunDynamics() = delete;

	// parameterized constructor
	SunDynamics(SpacecraftBody* pBody, Sun* pSun);

	// destructor
	~SunDynamics() = default;

	// forward declarations
	const Vector3 getAofBwrtIexpI() override;

	// access functions

	// setter functions
};

/*
** ----------- Class Definition ------------
*/ 
class SrpDynamics : public Dynamics
{
	Sun* _pSun { nullptr };
	
public:
	// default constructor
	SrpDynamics() = delete;

	// parameterized constructor
	SrpDynamics(SpacecraftBody* pBody, Sun* pSun);

	// destructor
	~SrpDynamics() = default;

	// forward declarations
	const Vector3 getAofBwrtIexpI() override;

	// access functions

	// setter functions
};

#endif  // DYNAMICS_HH
