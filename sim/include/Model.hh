// ------- Header Guard -------
#ifndef MODEL_HH  
#define MODEL_HH

// ------- Preprocessor directives -------
#include "Vector.hh"

// ------ Forward Declarations -------
class IntegratorData;


// ------- Class Definition -------
class Model
{
protected:
	const char* _pName { nullptr };
	IntegratorData* _pIntegratorData { nullptr };
	bool _isRegWithIntegrator { false };
	bool _atSolutionPoint { true };

public:
	// default constructor
	Model() = delete;

	// parameterized constructor
	Model(const char* name);

	// destructor
	~Model();

	// virtual functions
	virtual void updateDerivs() = 0;
	virtual void updateStateDependents() = 0;

	// forward declarations
	void registerStates(double& x, double& dx);
	void registerStates(Vector3& x, Vector3& dx);

	// access functions
	const char* getName() const { return _pName; }
	IntegratorData* getIntegratorData() const { return _pIntegratorData; }
	const bool& isRegisteredWithIntegrator() const { return _isRegWithIntegrator; }
	const bool& atSolutionPoint() const { return _atSolutionPoint; }

	// setter functions
	void setRegisteredWithIntegrator( const bool flag ) { _isRegWithIntegrator = flag; }
	void setSolutionPoint( const bool flag ) { _atSolutionPoint = flag; }

};

// ensure all inheritors of Model call updateDerivs() at end of constructor

#endif  // MODEL_HH
