// ------- Preprocessor directives -------
#include "Model.hh"
#include "Integrator.hh"
#include "OutputProducer.hh"
#include "Vector.hh"
#include <string>	// for std::string

// ------- Namespace directives -------
 
// ------- Class Definition -------
// Constructor
Model::Model(const std::string& name) : 
	OutputProducer(name),
	_name { name }
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

// register states with integrator (vector overload)
void Model::registerStates(Vector3& x, Vector3& dx)
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
