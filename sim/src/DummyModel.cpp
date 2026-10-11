// ------- Preprocessor directives -------
#include "DummyModel.hh"

// ------- Namespace directives -------
 
// ------- Class Definition -------
DummyModel::DummyModel(const char* pName) :
	Model(pName)
{
	
}

void DummyModel::initModel()
{
	// register states to be integrated
	registerStates(_r, _v);

	// register outputs with integrator
	registerOutput("position", _r);
	registerOutput("velocity", _v);
}

void DummyModel::updateDerivs()
{

}
void DummyModel::updateStateDependents()
{
	
}

