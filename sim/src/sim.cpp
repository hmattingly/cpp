// ------- Preprocessor directives -------
#include "Scheduler.hh"
#include "Integrator.hh"
#include "DummyModel.hh"
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
	double startTime { 0.0 };
	double endTime { 1.0 };
	double dt { 0.1 };

	// instantiate Scheduler object and set parameters
	Scheduler* pScheduler = new Scheduler(startTime, endTime);

	// build integrators
	ForwardEuler* pIntegrator = new ForwardEuler(dt);

	// build models
	DummyModel* pDummyModel = new DummyModel("Dumb Dumb");
	pIntegrator->registerModel(pDummyModel);	
	
	// run sim
	while (RUNNING != pScheduler->getStatus())
	{
		pScheduler->run();
	}

	// clean up
	delete pScheduler;
}
