// ------- Header Guard -------
#ifndef SPACECRAFT_HH  
#define SPACECRAFT_HH

// ------- Preprocessor directives -------
#include "Model.hh"
#include "Vector.hh"
#include "Dynamics.hh"
#include "SpacecraftBody.hh"
#include <cstddef>  // for std::size_t
#include <string>	// for std::string

// ------ Constants -------


// ------ Forward Declarations -------


// ------- Class Definition -------
class Spacecraft : public Model
{
	SpacecraftBody _body;
	DynamicsOptions _dynamicsOptions;
	Dynamics* _pDynamics[MAX_DYNAMIC] { nullptr };
	std::size_t _numDynamics { 0 };

public:
	// default constructor (disabled)
	Spacecraft() = delete;

	// parameterized constructor
	Spacecraft(const std::string& pName);

	// destructor
	~Spacecraft() = default;

	// forward declarations
	virtual void initModel() override;
	virtual void updateDerivs() override;
	virtual void updateStateDependents() override;

	// setter functions

	// access functions
	const SpacecraftBody& getSpacecraftBody() const { return _body; }
};


#endif  // SPACECRAFT_HH
