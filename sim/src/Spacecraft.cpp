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
Spacecraft::Spacecraft(const std::string& name, json inputFileData, Earth* pEarth, Sun* pSun, Moon* pMoon) :
	Model(name), _pEarth { pEarth }, _pSun { pSun }, _pMoon { pMoon }
{
	// build spacecraft body
	_pBody = new SpacecraftBody(pEarth);

	// get spacecraft initial state
	for ( std::size_t i { 0 }; i < 3; ++i )
	{
		_pBody->RofBwrtCexpI[i] = inputFileData["initialState"]["RofBwrtCexpI"][i].get<double>();
		_pBody->VofBwrtIexpI[i] = inputFileData["initialState"]["VofBwrtIexpI"][i].get<double>();
	}

	// get spacecraft parameters
	_pBody->AMR = inputFileData["areaToMassRatio"].get<double>();
	_pBody->CRd = inputFileData["diffuseReflectivity"].get<double>();
	_pBody->Cd  = inputFileData["dragCoefficient"].get<double>();

	// get dynamic models
	_dynamicsOptions.twoBody 	= inputFileData["dynamics"]["TwoBody"].get<bool>();
	_dynamicsOptions.j2 		= inputFileData["dynamics"]["J2"].get<bool>();
	_dynamicsOptions.j3 		= inputFileData["dynamics"]["J3"].get<bool>();
	_dynamicsOptions.j4 		= inputFileData["dynamics"]["J4"].get<bool>();
	_dynamicsOptions.sun 		= inputFileData["dynamics"]["Sun"].get<bool>();
	_dynamicsOptions.moon 		= inputFileData["dynamics"]["Moon"].get<bool>();
	_dynamicsOptions.srp 		= inputFileData["dynamics"]["SRP"].get<bool>();
	_dynamicsOptions.drag 		= inputFileData["dynamics"]["Drag"].get<bool>();

	// set output flag
	_outputFlag = inputFileData["outputFlag"].get<bool>();

	// populate initial values
	updateStateDependents();
	
}

void Spacecraft::initModel()
{
	// NOTE initModel() is executed when Model registered to Integrator

	// register ECI states to be integrated
	registerStates(_pBody->RofBwrtCexpI, _pBody->VofBwrtIexpI);
	registerStates(_pBody->VofBwrtIexpI, _pBody->AofBwrtIexpI);

	// register outputs with integrator
	registerOutput("RofBwrtCexpI", _pBody->RofBwrtCexpI);
	registerOutput("VofBwrtIexpI", _pBody->VofBwrtIexpI);
	registerOutput("AofBwrtIexpI", _pBody->AofBwrtIexpI);
	registerOutput("RofBwrtCexpE", _pBody->RofBwrtCexpE);
	registerOutput("VofBwrtIexpE", _pBody->VofBwrtIexpE);
	registerOutput("VofBwrtEexpE", _pBody->VofBwrtEexpE);
	registerOutput("RofBwrtCexpL", _pBody->RofBwrtCexpL);
	registerOutput("VofBwrtIexpL", _pBody->VofBwrtIexpL);
	registerOutput("RofBwrtCexpP", _pBody->RofBwrtCexpP);
	registerOutput("VofBwrtIexpP", _pBody->VofBwrtIexpP);

	registerOutput("HofBwrtCexpI", _pBody->HofBwrtCexpI);
	registerOutput("NofBwrtCexpIhat", _pBody->NofBwrtCexpIhat);

	registerOutput("a", _pBody->a);
	registerOutput("ecc", _pBody->ecc);
	registerOutput("inc", _pBody->inc);
	registerOutput("raan", _pBody->raan);
	registerOutput("aop", _pBody->aop);
	registerOutput("ta", _pBody->ta);

	registerOutput("aol", _pBody->aol);
	registerOutput("p", _pBody->p);
	registerOutput("b", _pBody->b);
	registerOutput("Rp", _pBody->Rp);
	registerOutput("Ra", _pBody->Ra);
	registerOutput("E", _pBody->E);
	registerOutput("M", _pBody->M);
	registerOutput("n", _pBody->n);
	registerOutput("P", _pBody->P);
	registerOutput("energy", _pBody->energy);
	registerOutput("fpa", _pBody->fpa);

	registerOutput("gcLat", _pBody->gcLat);
	registerOutput("gdLat", _pBody->gdLat);
	registerOutput("lon", _pBody->lon);
	registerOutput("alt", _pBody->alt);
	registerOutput("gcRA", _pBody->gcRA);
	registerOutput("gcDecl", _pBody->gcDecl);
	registerOutput("gmha", _pBody->gmha);

	// register applicable dynamics
	if ( true == _dynamicsOptions.twoBody )
	{
		_pDynamics[_numDynamics] = new TwoBodyDynamics(_pBody, _pEarth);
		++_numDynamics;
	}
	if ( true == _dynamicsOptions.j2 )
	{
		_pDynamics[_numDynamics] = new J2Dynamics(_pBody, _pEarth);
		++_numDynamics;
	}
	if ( true == _dynamicsOptions.j3 )
	{
		_pDynamics[_numDynamics] = new J3Dynamics(_pBody, _pEarth);
		++_numDynamics;
	}
	if ( true == _dynamicsOptions.j4 )
	{
		_pDynamics[_numDynamics] = new J4Dynamics(_pBody, _pEarth);
		++_numDynamics;
	}
	if ( true == _dynamicsOptions.sun )
	{
		_pDynamics[_numDynamics] = new SunDynamics(_pBody, _pSun);
		++_numDynamics;
	}
	if ( true == _dynamicsOptions.moon )
	{
		//
	}
	if ( true == _dynamicsOptions.drag )
	{
		_pDynamics[_numDynamics] = new DragDynamics(_pBody, _pEarth);
		++_numDynamics;
	}
	if ( true == _dynamicsOptions.srp )
	{
		_pDynamics[_numDynamics] = new SrpDynamics(_pBody, _pSun);
		++_numDynamics;
	}
	

	// set initialized flag
	_initialized = true;

}

// called after state (position and velocity) is updated to next timestep
void Spacecraft::updateStateDependents()
{
	_pBody->updateFromI( _atSolutionPoint );
}

// called after state dependents are updated to next timestep
void Spacecraft::updateDerivs()
{
	// reset acceleration
	_pBody->AofBwrtIexpI = { ZERO_VECTOR3 }; 

	// loop through each dynamics model and update acceleration term
	for ( std::size_t i { 0 }; i < _numDynamics; ++i )
	{
		_pBody->AofBwrtIexpI += _pDynamics[i]->getAofBwrtIexpI();
	}
}

// destructor
Spacecraft::~Spacecraft()
{
	for ( std::size_t i { 0 }; i < _numDynamics; ++i )
	{
		delete _pDynamics[i];
	}
	delete _pBody;
}
