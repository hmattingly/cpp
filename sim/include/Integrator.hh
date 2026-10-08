// ------- Header Guard -------
#ifndef INTEGRATOR_HH  
#define INTEGRATOR_HH

// ------- Preprocessor directives -------
#include "Scheduler.hh"
#include "Model.hh"

// ------- Class Definition -------
template <typename Model>
class Integrator
{
	using Vector = typename Model::Vector;

	Vector _X;
	Vector _k1;
	Vector _k2;
	Vector _k3;
	Vector _k4;

	double _h { Scheduler::getTimestep() };
	double _hd2 { _h / 2.0 };
	Model* _pObject { nullptr };
	

public:
	// default constructor
	Integrator();

	// parameterized constructor
	Integrator(Model* pObject);

	void update(double time);
};

#endif  // INTEGRATOR_HH
