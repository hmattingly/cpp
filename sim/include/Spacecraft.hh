// ------- Header Guard -------
#ifndef SPACECRAFT_HH  
#define SPACECRAFT_HH

// ------- Preprocessor directives -------
#include "Model.hh"
#include "Vector.hh"

// ------ Constants -------


// ------ Forward Declarations -------


// ------- Class Definition -------
class Spacecraft : public Model
{
	Vector3 _RofBwrtOexpECI {0.0, 1.0, 2.0};
	Vector3 _VofBwrtOexpECI {2.0, 4.0, 6.0};

public:
	// default constructor (disabled)
	Spacecraft() = delete;

	// parameterized constructor
	Spacecraft(const char* pName);

	// destructor
	~Spacecraft() = default;

	// forward declarations
	virtual void initModel() override;
	virtual void updateDerivs() override;
	virtual void updateStateDependents() override;
};


#endif  // SPACECRAFT_HH
