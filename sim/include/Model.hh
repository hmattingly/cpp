// ------- Header Guard -------
#ifndef MODEL_HH  
#define MODEL_HH

// ------- Preprocessor directives -------
#include "OutputProducer.hh"
#include "Vector.hh"
#include <string>			// for std::string

// ------ Forward Declarations -------
class Integrator;
class IntegratorData;

// ------- Class Definition -------
class Model : public OutputProducer
{
protected:
	const std::string _name { "no_name" };
	IntegratorData* _pIntegratorData { nullptr };
	const Integrator* _pIntegrator { nullptr };
	bool _atSolutionPoint { true };
	bool _initialized { false };

public:
	// default constructor
	Model() = delete;

	// parameterized constructor
	Model(const std::string& name);

	// destructor
	~Model();

	// virtual functions
	virtual void initModel() = 0;
	virtual void updateDerivs() = 0;
	virtual void updateStateDependents() = 0;

	// forward declarations
	void registerStates(double& x, double& dx);
	void registerStates(Vector3& x, Vector3& dx);

	// access functions
	const std::string& getName() const { return _name; }
	IntegratorData* getIntegratorData() const { return _pIntegratorData; }
	const Integrator* getIntegrator() const { return _pIntegrator; }
	const bool& atSolutionPoint() const { return _atSolutionPoint; }
	const bool& isInitialized() const { return _initialized; }

	// setter functions
	void setIntegrator( const Integrator* pIntegrator ) { _pIntegrator = pIntegrator; }
	void setSolutionPoint( const bool flag ) { _atSolutionPoint = flag; }

};

// ensure all inheritors of Model call updateDerivs() at end of constructor

#endif  // MODEL_HH
