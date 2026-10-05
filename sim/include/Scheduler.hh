// ------- Header Guard -------
#ifndef SCHEDULER_HH
#define SCHEDULER_HH

// ------- Preprocessor directives -------
#include <cassert>

// ------- Class Definition -------
class Scheduler
{
	// static member variables, shared across all instances of Scheduler
	static inline bool _exists { false };
	static inline bool _running { false };
	static inline double _timestep { 0.0 };
	static inline double _time { 0.0 };
	static inline double _startTime { 0.0 };
	static inline double _endTime { 0.0 };

public:

	// default constructor
	Scheduler();

	// destructor
	~Scheduler() = default;

	// forward declarations
	void start();
	void update();
	void reset();
	
	// access functions
	const bool& isRunning() const { return _running; }
	const double& getTimestep() const { return _timestep; }
	const double& getCurrentTime() const { return _time; }

	// setter functions
	void setStartEndTime(double startTime, double endTime)
	{ 
		_startTime = startTime; 
		_endTime = endTime;
	}
	void setNumSamples(int samples)
	{
		assert(samples > 0);
		_timestep = (_endTime - _startTime) / samples;

	}
	void setTimestep(double timestep)
	{
		if ( _startTime < _endTime )
		{
			assert(timestep > 0.0);
		}
		else if ( _startTime > _endTime )
		{
			assert(timestep < 0.0);
		}
		_timestep = timestep;
	}
	void setCurrentTime(double time)
	{ 
		if (_timestep > 0.0)
		{
			assert(time >= _startTime && time <= _endTime);
		}
		else if (_timestep < 0.0)
		{
			assert(time <= _startTime && time >= _endTime);
		}
		_time = time;
	}

};

#endif // SCHEDULER_HH
