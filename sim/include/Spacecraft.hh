// ------- Header Guard -------
#ifndef SPACECRAFT_HH  
#define SPACECRAFT_HH

// ------- Preprocessor directives -------
#include "Model.hh"
#include "Vector.hh"
#include "Dynamics.hh"
#include "InputParser.hh"
#include <cstddef>  // for std::size_t
#include <string>	// for std::string

// ------ Constants -------

// ------ Forward Declarations -------
class Earth;
class Sun;
class Moon;
class SpacecraftBody;

// ------- Class Definition -------
class Spacecraft : public Model
{
	Earth* _pEarth { nullptr };
	Sun* _pSun { nullptr };
	Moon* _pMoon { nullptr };

	SpacecraftBody* _pBody { nullptr };
	DynamicsOptions _dynamicsOptions;
	Dynamics* _pDynamics[MAX_DYNAMIC] { nullptr };
	std::size_t _numDynamics { 0 };

public:
	// default constructor (disabled)
	Spacecraft() = delete;

	// parameterized constructor
	Spacecraft(const std::string& name, json inputFileData, Earth* pEarth, Sun* pSun, Moon* pMoon);

	// destructor
	~Spacecraft();

	// forward declarations
	virtual void initModel() override;
	virtual void updateDerivs() override;
	virtual void updateStateDependents() override;

	// setter functions

	// access functions
	const SpacecraftBody* getSpacecraftBody() const { return _pBody; }
};


#endif  // SPACECRAFT_HH
