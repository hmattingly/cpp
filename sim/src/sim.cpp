// ------- Preprocessor directives -------
#include "Scheduler.hh"
#include <cstdio>

// ------- Namespace directives -------
 
// ------- User-Defined Functions -------
 
// ------- MAIN -------

int main(int argc, char* argv[])
{
	// display the program name and arguments passed to the program
	printf("--------------------------------\n");
	if (argc < 2)
	{
		printf("Executing %s with no arguments\n", argv[0]);
	}
	else
	{
		printf("Executing %s with arguments: ", argv[0]);
		for (int i { 1 }; i < argc; ++i)
		{
			printf("%s ", argv[i]);
		}
		printf("\n");
	}
	printf("--------------------------------\n");

	// set sim run time parameters
	int samples { 10 };
	double startTime { 0.0 };
	double endTime { 1.0 };

	// instantiate Scheduler object and set parameters
	Scheduler* scheduler = new Scheduler();
	scheduler->setStartEndTime(startTime, endTime);

	// build integrators
	Integrator* pIntegrator = new Integrator();
	
	// run sim
	scheduler->start();
	printf("Current time: %f\n", scheduler->getCurrentTime());
	while (true == scheduler->isRunning())
	{
		scheduler->update();
		printf("Current time: %f\n", scheduler->getCurrentTime());
	}

	// clean up
	delete scheduler;
}
