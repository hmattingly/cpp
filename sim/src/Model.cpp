// ------- Preprocessor directives -------
#include "Model.hh"
#include "Integrator.hh"

// ------- Namespace directives -------
 
// ------- Class Definition -------
// Constructor
Model::Model(const char* pName) : _pName { pName }
{

}

// register states with integrator
void Model::registerStates(double& x, double& dx)
{
	if ( nullptr == _pIntegratorData )
	{
		_pIntegratorData = new IntegratorData(this);
	}
	_pIntegratorData->addStates(x, dx);
}

// destructor
Model::~Model()
{
	delete _pIntegratorData;
}
