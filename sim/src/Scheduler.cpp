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
		// start Scheduler
		_status = RUNNING;

		// set double time
		_startTime = startTime;
		_endTime = endTime;
		_time = _startTime;

		// set integer time
		_iStartTime = double2iTime(_startTime);
		_iEndTime = double2iTime(_endTime);
		_iTime = double2iTime(_time);
	}
	else
	{
		printf("Error: Scheduler already exists!\n");
		std::exit(EXIT_FAILURE);
	}
	
}

// convert to integer time (quantization)
ITIME Scheduler::double2iTime(const double time)
{
	if ( time > 0.0 )
	{
		return (static_cast<ITIME>( time / FLOAT_TOL + 0.5 ));
	}
	else if ( time < 0.0 )
	{
		return (static_cast<ITIME>( time / FLOAT_TOL - 0.5 ));
	}
	else
	{
		return static_cast<ITIME>(time);
	}
}

// update the scheduler time by one timestep
void Scheduler::run()
{
	_checkExitConditions();

	if ( RUNNING == _status )
	{
		// from each integrator get min nextUpdateTime
		// ensure integrators evaluate at last time step
		double minUpdateTime { MAX_DOUBLE };
		for ( std::size_t i { 0 }; i < _numIntegrators; ++i )
		{
			// only adjust integrator timestep while at a solution point
			if ( true == _pIntegratorArray[i]->atSolutionPoint() )
			{
				if ( double2iTime(_pIntegratorArray[i]->getTime() + _pIntegratorArray[i]->getTimestep()) > _iEndTime )
				{
					_pIntegratorArray[i]->setTimestep( _endTime - _pIntegratorArray[i]->getTime() );
				}
			}
			minUpdateTime = MIN(minUpdateTime, _pIntegratorArray[i]->getNextUpdateTime());
		}

		// set time to next update time
		_time = minUpdateTime;
		_iTime = double2iTime(_time);

		// perform integration to update states of integrators that are ready
		for ( std::size_t i { 0 }; i < _numIntegrators; ++i )
		{
			if ( _iTime == double2iTime(_pIntegratorArray[i]->getNextUpdateTime()) )
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
	// check if we've reached the end of the sim with all integrators at solution point
	if ( _iTime == _iEndTime )
	{
		for ( std::size_t i { 0 }; i < _numIntegrators; ++i )
		{
			if ( false == _pIntegratorArray[i]->atSolutionPoint() )
			{
				return;
			}
		}
		_status = ENDTIME;
	}
	else if ( _iTime > _iEndTime )
	{
		_status = ERROR;
	}
}
