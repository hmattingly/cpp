// ------- Preprocessor directives -------
#include "InputParser.hh"
#include "Scheduler.hh"
#include "Integrator.hh"
#include "Spacecraft.hh"
#include <cstdio>		// for printf
#include <filesystem>  	// for std::filesystem
#include <string>		// for std::string


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

	// ------- Sim Inputs -------
	const std::string inputFileName { "sim.json" };
	InputParser* pInputFile = new InputParser(inputFileName);
	double simStartTime { pInputFile->inputFileData["simStartTime"].get<double>() };
	double simEndTime { pInputFile->inputFileData["simEndTime"].get<double>() };
	// ---------------------------

	// instantiate Scheduler object and set parameters
	Scheduler* pScheduler = new Scheduler(simStartTime, simEndTime);

	// build integrators
	double timeStepRK4 { pInputFile->inputFileData["timeStepRK4"].get<double>() };
	RK4* pIntegrator = new RK4(timeStepRK4);

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
