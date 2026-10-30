// ------- Preprocessor directives -------
#include "InputParser.hh"
#include "Scheduler.hh"
#include "Integrator.hh"
#include "Spacecraft.hh"
#include "Epoch.hh"
#include <chrono>		// for steady_clock
#include <cstdio>		// for printf
#include <filesystem>  	// for std::filesystem
#include <string>		// for std::string


// ------- Namespace directives -------
 
// ------- User-Defined Functions -------
 
// ------- MAIN -------
int main(int argc, char* argv[])
{
	auto simRealStartTime { std::chrono::steady_clock::now() };
    
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

	double simRunTime 	{ pInputFile->inputFileData["simRunTime"].get<double>() };
	double timeStepRK4 	{ pInputFile->inputFileData["timeStepRK4"].get<double>() };

	int year 			{ pInputFile->inputFileData["epoch"]["year"].get<int>() };
	int month 			{ pInputFile->inputFileData["epoch"]["month"].get<int>() };
	int day 			{ pInputFile->inputFileData["epoch"]["day"].get<int>() };
	double utc 			{ pInputFile->inputFileData["epoch"]["utc"].get<double>() };
	// ---------------------------

	// instantiate Scheduler object and set parameters
	Epoch* pEpoch = new Epoch(year, month, day, utc);
	Scheduler* pScheduler = new Scheduler(pEpoch, simRunTime);

	// build integrators
	RK4* pIntegratorRK4 = new RK4(timeStepRK4);

	// build models
	Spacecraft* pSpacecraft = new Spacecraft("Spacecraft");
	pIntegratorRK4->registerModel(pSpacecraft);
	
	// run sim
	pScheduler->start();
	while (RUNNING == pScheduler->getStatus())
	{
		pScheduler->run();
	}
	// display sim run time
	auto simRealEndTime { std::chrono::steady_clock::now() };
    std::chrono::duration<double> elapsedTime = simRealEndTime - simRealStartTime;
    printf("Execution Time: %.2f seconds\n", elapsedTime.count());
	printf("Exit Code: %d\n", pScheduler->getStatus());
	printf("--------------------------------\n");

	// clean up
	delete pInputFile;
	delete pScheduler;
	delete pIntegratorRK4;
	delete pSpacecraft;
	delete pEpoch;
}
