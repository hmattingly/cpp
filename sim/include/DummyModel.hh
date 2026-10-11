// ------- Header Guard -------
#ifndef DUMMYMODEL_HH  
#define DUMMYMODEL_HH

// ------- Preprocessor directives -------
#include "Model.hh"
#include "Vector.hh"

// ------ Constants -------


// ------ Forward Declarations -------


// ------- Class Definition -------
class DummyModel : public Model
{
	Vector3 _r {0.0, 1.0, 2.0};
	Vector3 _v {2.0, 4.0, 6.0};

public:
	// default constructor (disabled)
	DummyModel() = delete;

	// parameterized constructor
	DummyModel(const char* pName);

	// destructor
	~DummyModel() = default;

	// forward declarations
	virtual void updateDerivs() override;
	virtual void updateStateDependents() override;
};


#endif
