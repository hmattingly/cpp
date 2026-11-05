// ------- Preprocessor directives -------
#include "Spacecraft.hh"
#include "Scheduler.hh"
#include "InputParser.hh"
#include "Dynamics.hh"
#include "Vector.hh"
#include <cassert>	// for assert()
#include <cstddef>  // for std::size_t
#include <string>	// for std::string

// ------- Namespace directives -------

// ------- Class Definition -------
Spacecraft::Spacecraft(const std::string& name, Earth* pEarth) :
	Model(name), _pEarth { pEarth }
{
	// ------- Spacecraft Inputs -------
	const std::string inputFileName { "spacecraft.json" };
	InputParser* pInputFile = new InputParser(inputFileName);

	// build spacecraft body
	_body = new SpacecraftBody(pEarth);

	// get spacecraft initial state
	for ( std::size_t i { 0 }; i < 3; ++i )
	{
		_body->RwrtOexpN[i] = pInputFile->inputFileData["initialState"]["RwrtOexpN"][i].get<double>();
		_body->VwrtNexpN[i] = pInputFile->inputFileData["initialState"]["VwrtNexpN"][i].get<double>();
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
	registerStates(_body->RwrtOexpN, _body->VwrtNexpN);
	registerStates(_body->VwrtNexpN, _body->AwrtNexpN);

	// register outputs with integrator
	registerOutput("RwrtOexpN", _body->RwrtOexpN);
	registerOutput("VwrtNexpN", _body->VwrtNexpN);
	registerOutput("AwrtNexpN", _body->AwrtNexpN);
	registerOutput("RwrtOexpE", _body->RwrtOexpE);
	registerOutput("VwrtNexpE", _body->VwrtNexpE);
	registerOutput("VwrtEexpE", _body->VwrtEexpE);
	registerOutput("RwrtOexpL", _body->RwrtOexpL);
	registerOutput("VwrtNexpL", _body->VwrtNexpL);
	registerOutput("RwrtOexpP", _body->RwrtOexpP);
	registerOutput("VwrtNexpP", _body->VwrtNexpP);

	registerOutput("HwrtOexpN", _body->HwrtOexpN);
	registerOutput("NwrtOexpNhat", _body->NwrtOexpNhat);

	registerOutput("a", _body->a);
	registerOutput("ecc", _body->ecc);
	registerOutput("inc", _body->inc);
	registerOutput("raan", _body->raan);
	registerOutput("aop", _body->aop);
	registerOutput("ta", _body->ta);

	registerOutput("aol", _body->aol);
	registerOutput("p", _body->p);
	registerOutput("b", _body->b);
	registerOutput("Rp", _body->Rp);
	registerOutput("Ra", _body->Ra);
	registerOutput("E", _body->E);
	registerOutput("M", _body->M);
	registerOutput("n", _body->n);
	registerOutput("P", _body->P);
	registerOutput("energy", _body->energy);
	registerOutput("fpa", _body->fpa);

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
		_pDynamics[_numDynamics] = new J3Dynamics(_body);
		++_numDynamics;
	}
	if ( true == _dynamicsOptions.j4 )
	{
		_pDynamics[_numDynamics] = new J4Dynamics(_body);
		++_numDynamics;
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
	_body->updateFromN( _atSolutionPoint );
}

// called after state dependents are updated to next timestep
void Spacecraft::updateDerivs()
{
	// reset acceleration
	_body->AwrtNexpN = { ZERO_VECTOR3 }; 

	// loop through each dynamics model and update acceleration term
	for ( std::size_t i { 0 }; i < _numDynamics; ++i )
	{
		_body->AwrtNexpN += _pDynamics[i]->getAwrtNexpN();
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
