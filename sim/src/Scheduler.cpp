// ------- Preprocessor directives -------
#include "Scheduler.hh"
#include "Integrator.hh"
#include "Constants.hh"
#include <cstdio>   // for printf()
#include <cstdlib>  // for std::exit()
#include <cassert>	// for assert()
#include <cstddef>  // for std::size_t

// ------- Namespace directives -------
using namespace Constants;
 
// ------- Class Definition -------
// Constructor
Scheduler::Scheduler(const double startTime, const double endTime)
{
	assert(startTime < endTime);

	// check if the Scheduler already exists, 
	if ( UNINITIALIZED == _status )
	{
		_status = RUNNING;
		_startTime = startTime;
		_endTime = endTime;
		_time = _startTime;
	}
	else
	{
		printf("Error: Scheduler already exists!\n");
		std::exit(EXIT_FAILURE);
	}
	
}

// update the scheduler time by one timestep
void Scheduler::run()
{
	_checkExitConditions();

	if ( RUNNING == _status )
	{
		// from each integrator get min nextUpdateTime
		double minUpdateTime { MAX_DOUBLE };
		for ( std::size_t i { 0 }; i < _numIntegrators; ++i )
		{
			if ( _pIntegratorArray[i] != nullptr )
			{
				minUpdateTime = MIN(minUpdateTime, _pIntegratorArray[i]->getNextUpdateTime());
				
			}
		}

		// TODO consider better stopping condition at endTime

		// set time to next update time
		_time = minUpdateTime;

		// perform integration to update states of integrators that are ready
		for ( std::size_t i { 0 }; i < _numIntegrators; ++i )
		{
			if ( _pIntegratorArray[i] != nullptr && _time == _pIntegratorArray[i]->getNextUpdateTime() )
			{
				_pIntegratorArray[i]->updateStates();
				_pIntegratorArray[i]->updateStateDependents();
				_pIntegratorArray[i]->updateDerivs();
			}
		}
	}
}

// register integrator with the scheduler
void Scheduler::registerIntegrator(Integrator* pIntegrator)
{
	if ( nullptr == pIntegrator )
	{
		printf("Error: Cannot register null Integrator to Scheduler!\n");
		std::exit(EXIT_FAILURE);
	}

	if ( _numIntegrators >= MAX_INTEGRATORS )
	{
		printf("Error: Maximum number of integrators reached!\n");
		std::exit(EXIT_FAILURE);
	}
	
	_pIntegratorArray[_numIntegrators] = pIntegrator;
	_numIntegrators++;
}

// check exit conditions
void Scheduler::_checkExitConditions()
{
	// check if we've reached the end of the sim
	if ( _time >= _endTime )
	{
		_status = ENDTIME;
	}

}
