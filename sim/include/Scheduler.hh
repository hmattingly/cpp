// ------- Header Guard -------
#ifndef SCHEDULER_HH
#define SCHEDULER_HH

// ------- Preprocessor directives -------
#include <cassert>  // for assert()

// ------ Constants -------
inline constexpr int MAX_INTEGRATORS { 10 };

// ------ Forward Declarations -------
class Integrator;

// ------- Enum Definition -------
enum SchedulerStatus
{
	UNINITIALIZED,
	RUNNING,
	ENDTIME,
	FORCEDEND,
	ERROR
};

// ------- Class Definition -------
class Scheduler
{
	// static member variables, shared across all instances of Scheduler
	static inline SchedulerStatus _status { UNINITIALIZED };

	static inline double _time { 0.0 };
	static inline double _startTime { 0.0 };
	static inline double _endTime { 0.0 };

	static inline Integrator* _pIntegratorArray[MAX_INTEGRATORS] { nullptr };
	static inline std::size_t _numIntegrators { 0 };

	void _checkExitConditions();

public:

	// default constructor
	Scheduler() = delete;

	// parameterized constructor
	Scheduler(const double startTime, const double endTime);

	// destructor
	~Scheduler() = default;

	// forward declarations
	void run();
	static void registerIntegrator(Integrator* pIntegrator);
	
	// access functions
	static const SchedulerStatus& getStatus() { return _status; }
	static const double& getCurrentTime() { return _time; }

	// setter functions
	static void setCurrentTime(const double time)
	{ 
		assert(time >= _startTime && time <= _endTime);
		_time = time;
	}

};

#endif // SCHEDULER_HH
