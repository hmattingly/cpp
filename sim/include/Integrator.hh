// ------- Header Guard -------
#ifndef INTEGRATOR_HH  
#define INTEGRATOR_HH

// ------- Preprocessor directives -------
#include "Scheduler.hh"
#include "Vector.hh"
#include <cstddef>  // for std::size_t

// ------ Constants -------
inline constexpr int MAX_NX { 128 };		// max number of state variables for any model
inline constexpr int MAX_MODELS { 10 };	// max number of models per integrator

// ------ Forward Declarations -------
class Model;

// ------- Class Definition -------
class IntegratorData
{
	double* pState[MAX_NX] { nullptr };
	double* pDState[MAX_NX] { nullptr };
	std::size_t nX { 0 };
	Model* pModel { nullptr };

	friend class ForwardEuler;
	friend class RK4;

public:
	// default constructor (disabled)
	IntegratorData() = delete;

	// parameterized constructor
	IntegratorData(Model* pModel);

	// destructor
	~IntegratorData() = default;

	// forward declarations
	void addStates(double& x, double& dx);
	void addStates(Vector3& x, Vector3& dx);

	// access functions
	
};

// ------- Class Definition -------
class Integrator
{
protected:
	double _dt { 0.0 };
	double _time { 0.0 };
	Model* _pModelArray[MAX_MODELS] { nullptr };
	std::size_t _numModels { 0 };
	double _nextUpdateTime { 0.0 };
	bool _atSolutionPoint { true };

public:
	// default constructor (disabled)
	Integrator() = delete;

	// parameterized constructor
	Integrator(const double dt);

	// destructor
	virtual ~Integrator() = default;

	// forward declarations
	virtual void updateStates() = 0;
	void updateStateDependents();
	void updateDerivs();
	void registerModel(Model* pModel);

	// access functions
	const double& getTime() const { return _time; }
	const double& getTimestep() const { return _dt; }
	const double& getNextUpdateTime() const { return _nextUpdateTime; }
	const bool& atSolutionPoint() const { return _atSolutionPoint; }

	// setter functions
	virtual void setNextUpdateTime() = 0;
	virtual void setTimestep(const double dt) = 0;
};

// ------- Class Definition -------
class ForwardEuler : public Integrator
{

public:
	// default constructor (disabled)
	ForwardEuler() = delete;

	// parameterized constructor
	ForwardEuler(const double dt);

	// destructor
	~ForwardEuler() = default;

	// forward declarations
	void updateStates() override;

	// setter functions
	void setNextUpdateTime() override { _nextUpdateTime = _time + _dt; }
	void setTimestep(const double dt) override;
};

// ------- Class Definition -------
class RK4 : public Integrator
{
	double _dt2 { 0.0 };
	double _dt3 { 0.0 };
	double _dt6 { 0.0 };
	int _step { 0 };
	double _state0[MAX_MODELS][MAX_NX] { NULL };
	double _k1[MAX_MODELS][MAX_NX] { NULL };
	double _k2[MAX_MODELS][MAX_NX] { NULL };
	double _k3[MAX_MODELS][MAX_NX] { NULL };
	double _k4[MAX_MODELS][MAX_NX] { NULL };

public:
	// default constructor (disabled)
	RK4() = delete;

	// parameterized constructor
	RK4(const double dt);

	// destructor
	~RK4() = default;

	// forward declarations
	void updateStates() override;

	// setter functions
	void setNextUpdateTime() override { _nextUpdateTime = _time + _dt2; }
	void setTimestep(const double dt) override;
	

};

#endif  // INTEGRATOR_HH
