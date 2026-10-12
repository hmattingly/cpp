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
	registerStates(_r, _v);

	// register outputs with integrator
	registerOutput("position", _r);
	registerOutput("velocity", _v);
}

void Spacecraft::updateDerivs()
{

}
void Spacecraft::updateStateDependents()
{
	
}

