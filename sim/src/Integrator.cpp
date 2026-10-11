// ------- Preprocessor directives -------
#include "Integrator.hh"
#include "Model.hh"
#include <cstdio>   // for printf()
#include <cstdlib>  // for std::exit()
#include <cstddef>  // for std::size_t
#include <cassert>  // for assert()

// ------- Namespace directives -------
 
// ------- Class Definition -------
// Constructor
IntegratorData::IntegratorData(Model* pNewModel) :
	pModel { pNewModel }
{
	if ( nullptr == pNewModel )
	{
		printf("Error: Cannot register null Model to IntegratorData!\n");
		std::exit(EXIT_FAILURE);
	}
}

// set the state variables to be integrated
void IntegratorData::addStates(double& state, double& dstate)
{
	// check if the max number of state variables has been reached
	if ( nX >= MAX_NX )
	{
		printf("Error: Maximum number of state variables exceeded in %s!\n", pModel->getName());
		std::exit(EXIT_FAILURE);
	}

	// check if the state variable has already been set
	for (std::size_t i { 0 }; i < nX; ++i)
	{
		if ( &state == pState[i] )
		{
			printf("Error: %s state variable already set!\n", pModel->getName());
			std::exit(EXIT_FAILURE);
		}
		else if ( &dstate == pDState[i] )
		{
			printf("Error: %s derivative variable already set!\n", pModel->getName());
			std::exit(EXIT_FAILURE);
		}
	}

	// add variable pointers to the state and dstate arrays
	pState[nX] = &state;
	pDState[nX] = &dstate;
	++nX;
}

// set the state variables to be integrated (overload for Vector3)
void IntegratorData::addStates(Vector3& x, Vector3& dx)
{
	// add vectors to state and dstate arrays
	for (int i { 0 }; i < 3; ++i)
	{
		addStates(x[i], dx[i]);
	}
}

// ------- Class Definition -------
// constructor
Integrator::Integrator(const double dt) :
	_dt { dt }
{
	// only support positive values of dt
	assert(dt > 0.0);

	// add integrator to Scheduler's integrator array
	Scheduler::registerIntegrator(this);
}

// register model
void Integrator::registerModel(Model* pModel)
{
	if ( nullptr == pModel )
	{
		printf("Error: Cannot register null Model to Integrator!\n");
		std::exit(EXIT_FAILURE);
	}

	// check if model has already been registered
	if ( true == pModel->isRegisteredWithIntegrator() )
	{
		printf("Error: Model %s already registered with Integrator!\n", pModel->getName());
		std::exit(EXIT_FAILURE);
	}

	// check if max number of model reached
	if ( _numModels >= MAX_MODELS )
	{
		printf("Error: Maximum number of models reached!\n");
		std::exit(EXIT_FAILURE);
	}

	// check if model has Integrator Data
	if ( nullptr == pModel->getIntegratorData() )
	{
		printf("Warning: Model %s registered with no IntegratorData!\n", pModel->getName());
	}

	// add model to registry
	_pModelArray[_numModels] = pModel;
	_numModels++;

	// set model registered flag
	pModel->setRegisteredWithIntegrator( true );
}

// update the derivative variables of all models in the integrator
void Integrator::updateDerivs()
{
	// loop through each model and update derivatives
	for ( std::size_t i { 0 }; i < _numModels; ++i )
	{
		_pModelArray[i]->updateDerivs();
	}
}

// update the state variables of all models in the integrator
void Integrator::updateStateDependents()
{
	// loop through each model and update variables that depend on state
	for ( std::size_t i { 0 }; i < _numModels; ++i )
	{
		_pModelArray[i]->updateStateDependents();
	}
}


// ------- Class Definition -------
// constructor
ForwardEuler::ForwardEuler(const double dt) :
	Integrator(dt)
{
	_time = Scheduler::getCurrentTime();
	setNextUpdateTime();
}

void ForwardEuler::setTimestep(const double dt)
{
	_dt = dt;
	setNextUpdateTime();
}

void ForwardEuler::updateStates()
{
	// loop through each model and update
	IntegratorData* pIntegratorData { nullptr };
	for ( std::size_t i { 0 }; i < _numModels; ++i )
	{
		pIntegratorData = _pModelArray[i]->getIntegratorData();

		if ( nullptr != pIntegratorData )
		{
			for ( std::size_t j { 0 }; j < pIntegratorData->nX; ++j )
			{
				// estimate state using Forward Euler
				  // y(t) = y(t-1) + dt * y'(t-1)
				*(pIntegratorData->pState[j]) += _dt * (*(pIntegratorData->pDState[j]));
			}
		}
	}

	// set nextUpdateTime
	_time = Scheduler::getCurrentTime();
	setNextUpdateTime();
}

// ------- Class Definition -------
// constructor
RK4::RK4(const double dt) :
	Integrator(dt),
	_dt2 { dt / 2.0 },
	_dt3 { dt / 3.0 },
	_dt6 { dt / 6.0 }
{
	_time = Scheduler::getCurrentTime();
	_nextUpdateTime = _time;
}

void RK4::setTimestep(const double dt)
{
	_dt = dt;
	_dt2 = dt / 2.0;
	_dt3 = dt / 3.0;
	_dt6 = dt / 6.0;
	setNextUpdateTime();
}

void RK4::updateStates()
{
	
	IntegratorData* pIntegratorData { nullptr };

	// RK4 performs at 4 steps:
	  // k1 = f(t, x)
	  // k2 = f(t+h/2, x+h/2*k1)
	  // k3 = f(t+h/2, x+h/2*k2)
	  // k4 = f(t+h, x+h*k3); x(t+h) = x(t)+h/6*(k1+2*k2+2*k3+k4)
	switch ( _step )
	{
	case 0:
		// loop through each model and update
		for ( std::size_t i { 0 }; i < _numModels; ++i )
		{
			// set solution to invalid
			_atSolutionPoint = false;
			_pModelArray[i]->setSolutionPoint( false );

			pIntegratorData = _pModelArray[i]->getIntegratorData();
			if ( nullptr != pIntegratorData )
			{
				for ( std::size_t j { 0 }; j < pIntegratorData->nX; ++j )
				{
					_state0[i][j] = *(pIntegratorData->pState[j]);
					_k1[i][j] = *(pIntegratorData->pDState[j]);
					*(pIntegratorData->pState[j]) = _state0[i][j] + _dt2 * _k1[i][j];
				}
			}
		}
		// set nextUpdateTime now at t + dt/2
		_time = Scheduler::getCurrentTime();
		setNextUpdateTime();

		break;

	case 1:
		// loop through each model and update
		for ( std::size_t i { 0 }; i < _numModels; ++i )
		{
			pIntegratorData = _pModelArray[i]->getIntegratorData();
			if ( nullptr != pIntegratorData )
			{
				for ( std::size_t j { 0 }; j < pIntegratorData->nX; ++j )
				{
					_k2[i][j] = *(pIntegratorData->pDState[j]);
					*(pIntegratorData->pState[j]) = _state0[i][j] + _dt2 * _k2[i][j];
				}
			}
		}
		// do not update step time
		break;

	case 2:
		// loop through each model and update
		for ( std::size_t i { 0 }; i < _numModels; ++i )
		{
			pIntegratorData = _pModelArray[i]->getIntegratorData();
			if ( nullptr != pIntegratorData )
			{
				for ( std::size_t j { 0 }; j < pIntegratorData->nX; ++j )
				{
					_k3[i][j] = *(pIntegratorData->pDState[j]);
					*(pIntegratorData->pState[j]) = _state0[i][j] + _dt * _k3[i][j];
				}
			}
		}
		// set nextUpdateTime now at t + dt
		_time = Scheduler::getCurrentTime();
		setNextUpdateTime();

		break;

	case 3:
		// loop through each model and update
		for ( std::size_t i { 0 }; i < _numModels; ++i )
		{
			pIntegratorData = _pModelArray[i]->getIntegratorData();
			if ( nullptr != pIntegratorData )
			{
				for ( std::size_t j { 0 }; j < pIntegratorData->nX; ++j )
				{
					_k4[i][j] = *(pIntegratorData->pDState[j]);
					*(pIntegratorData->pState[j]) = _state0[i][j]
													+ _dt6 * _k1[i][j]
													+ _dt3 * _k2[i][j]
													+ _dt3 * _k3[i][j]
													+ _dt6 * _k4[i][j];
				}
			}
			// set solution to valid
			_atSolutionPoint = true;
			_pModelArray[i]->setSolutionPoint( true );
		}
		// do not update step time
		break;
	}

	// increment to next step of RK4
	_step = (_step + 1) % 4;
		
}

