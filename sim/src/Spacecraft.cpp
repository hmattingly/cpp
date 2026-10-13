// ------- Preprocessor directives -------
#include "Spacecraft.hh"

// ------- Namespace directives -------
 
// ------- Class Definition -------
Spacecraft::Spacecraft(const char* pName) :
	Model(pName)
{
	
}

void Spacecraft::initModel()
{
	// register states to be integrated
	registerStates(_RofBwrtOexpECI, _VofBwrtOexpECI);

	// register outputs with integrator
	registerOutput("position", _RofBwrtOexpECI);
	registerOutput("velocity", _VofBwrtOexpECI);
}

void Spacecraft::updateDerivs()
{

}
void Spacecraft::updateStateDependents()
{
	
}

