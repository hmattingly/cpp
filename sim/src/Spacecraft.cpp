// ------- Preprocessor directives -------
#include "Spacecraft.hh"
#include "InputParser.hh"
#include "Dynamics.hh"
#include "Vector.hh"
#include <cassert>	// for assert()
#include <cstddef>  // for std::size_t
#include <string>	// for std::string

// ------- Namespace directives -------

// ------- Class Definition -------
Spacecraft::Spacecraft(const std::string& name) :
	Model(name)
{
	// ------- Spacecraft Inputs -------
	const std::string inputFileName { "spacecraft.json" };
	InputParser* pInputFile = new InputParser(inputFileName);

	// build spacecraft body
	_body = new SpacecraftBody();

	// get spacecraft initial state
	for ( std::size_t i { 0 }; i < 3; ++i )
	{
		_body->RwrtOexpN[i] = pInputFile->inputFileData["initialState"]["RwrtOexpN"][i].get<double>();
		_body->VwrtOexpN[i] = pInputFile->inputFileData["initialState"]["VwrtOexpN"][i].get<double>();
	}

	// get spacecraft parameters
	_body->AMR = pInputFile->inputFileData["areaToMassRatio"].get<double>();
	_body->CRd = pInputFile->inputFileData["diffuseReflectivity"].get<double>();
	_body->Cd  = pInputFile->inputFileData["dragCoefficient"].get<double>();

	// get dynamic models
	_dynamicsOptions.twoBody 	= pInputFile->inputFileData["dynamics"]["TwoBody"].get<bool>();
	_dynamicsOptions.j2 		= pInputFile->inputFileData["dynamics"]["J2"].get<bool>();
	_dynamicsOptions.j3 		= pInputFile->inputFileData["dynamics"]["J3"].get<bool>();
	_dynamicsOptions.j4 		= pInputFile->inputFileData["dynamics"]["J4"].get<bool>();
	_dynamicsOptions.srp 		= pInputFile->inputFileData["dynamics"]["SRP"].get<bool>();
	_dynamicsOptions.drag 		= pInputFile->inputFileData["dynamics"]["Drag"].get<bool>();

	// free up memory
	delete pInputFile;
}

void Spacecraft::initModel()
{
	// NOTE initModel() is executed when Model registered to Integrator

	// register ECI states to be integrated
	registerStates(_body->RwrtOexpN, _body->VwrtOexpN);
	registerStates(_body->VwrtOexpN, _body->AwrtOexpN);

	// register outputs with integrator
	registerOutput("RwrtOexpN", _body->RwrtOexpN);
	registerOutput("VwrtOexpN", _body->VwrtOexpN);
	registerOutput("AwrtOexpN", _body->AwrtOexpN);
	// registerOutput("RwrtOexpE", _body->RwrtOexpE);
	// registerOutput("VwrtOexpE", _body->VwrtOexpE);
	registerOutput("RwrtOexpL", _body->RwrtOexpL);
	registerOutput("VwrtOexpL", _body->VwrtOexpL);
	registerOutput("RwrtOexpP", _body->RwrtOexpP);
	registerOutput("VwrtOexpP", _body->VwrtOexpP);
	registerOutput("kepOE", _body->kepOE);

	// register applicable dynamics
	if ( true == _dynamicsOptions.twoBody )
	{
		_pDynamics[_numDynamics] = new TwoBodyDynamics(_body);
		++_numDynamics;
	}
	if ( true == _dynamicsOptions.j2 )
	{
		_pDynamics[_numDynamics] = new J2Dynamics(_body);
		++_numDynamics;
	}
	if ( true == _dynamicsOptions.j3 )
	{
		//
	}
	if ( true == _dynamicsOptions.j4 )
	{
		//
	}
	if ( true == _dynamicsOptions.srp )
	{
		//
	}
	if ( true == _dynamicsOptions.drag )
	{
		//
	}

	// set initialized flag
	_initialized = true;

}

// called after state (position and velocity) is updated to next timestep
void Spacecraft::updateStateDependents()
{
	_body->updateFromN();
}

// called after state dependents are updated to next timestep
void Spacecraft::updateDerivs()
{
	// reset acceleration
	_body->AwrtOexpN = { ZERO_VECTOR3 }; 

	// loop through each dynamics model and update acceleration term
	for ( std::size_t i { 0 }; i < _numDynamics; ++i )
	{
		_body->AwrtOexpN += _pDynamics[i]->getAwrtOexpN();
	}
}


// destructor
Spacecraft::~Spacecraft()
{
	for ( std::size_t i { 0 }; i < _numDynamics; ++i )
	{
		delete _pDynamics[i];
	}
	delete _body;
}
