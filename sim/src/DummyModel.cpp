// ------- Preprocessor directives -------
#include "DummyModel.hh"

// ------- Namespace directives -------
 
// ------- Class Definition -------
DummyModel::DummyModel(const char* pName) :
	Model(pName)
{
	registerStates(_r, _v);
}

void DummyModel::updateDerivs()
{

}
void DummyModel::updateStateDependents()
{
	
}

