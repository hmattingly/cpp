// ------- Preprocessor directives -------
#include "InputParser.hh"
#include "Scheduler.hh"
#include "Integrator.hh"
#include "Spacecraft.hh"
#include <cstdio>		// for printf
#include <filesystem>  	// for std::filesystem
#include <string>		// for string


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
	printf("Writing outputs to %s%s\n", std::filesystem::current_path().c_str(), "/outputs");
	printf("--------------------------------\n");

	// ------- Inputs -------
	std::string pInputFileName { "sim.json" };
	InputParser* pInputFile = new InputParser(pInputFileName);

	// set sim run time parameters
	double startTime { 0.0 };
	double endTime { 1.3 };
	double dt { 0.5 };
	// ---------------------------

	// instantiate Scheduler object and set parameters
	Scheduler* pScheduler = new Scheduler(startTime, endTime);

	// build integrators
	RK4* pIntegrator = new RK4(dt);

	// build models
	Spacecraft* pSpacecraft = new Spacecraft("Spacecraft");
	pIntegrator->registerModel(pSpacecraft);
	
	// run sim
	pScheduler->start();
	while (RUNNING == pScheduler->getStatus())
	{
		pScheduler->run();
	}

	// clean up
	delete pInputFile;
	delete pScheduler;
	delete pIntegrator;
	delete pSpacecraft;
}
