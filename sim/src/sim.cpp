/*
** ------- Preprocessor directives -------
*/ 
#include "InputParser.hh"
#include "Scheduler.hh"
#include "Integrator.hh"
#include "Spacecraft.hh"
#include "CelestialBody.hh"
#include "Observer.hh"
#include <chrono>		// for steady_clock
#include <cstdio>		// for printf
#include <cstddef>  	// for std::size_t
#include <filesystem>  	// for std::filesystem
#include <string>		// for std::string
#include <vector>		// for std::vector

/*
** -------------- Constants ---------------
*/ 

/*
** -------- Forward Declarations ----------
*/ 

/*
** --------- Namespace directives ---------
*/ 

/*
** -------- User-Defined Functions --------
*/ 

/*
** ------------ Main Function -------------
*/ 
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
	InputParser* pSimConfigFile = new InputParser( "sim.json" );
	InputParser* pSpacecraftConfigFile = new InputParser( "spacecraft.json" );
	InputParser* pObserverConfigFile = new InputParser( "observer.json" );
	// ---------------------------

	// instantiate Scheduler object and set parameters
	Scheduler* pScheduler = new Scheduler(pSimConfigFile);

	// build integrators
	RK4* pIntegratorRK4 = new RK4(pSimConfigFile);

	// build Earth model
	Earth* pEarth = new Earth();
	pIntegratorRK4->registerModel(pEarth);  // ensure Earth is registered first

	// build spacecrafts
	const std::size_t numSpacecraft { pSpacecraftConfigFile->inputFileData.size() };
	std::vector<Spacecraft*> pSpacecraftArray ( numSpacecraft, nullptr );
	std::size_t i { 0 };
	for ( const auto& [spacecraftName, spacecraftConfig] : pSpacecraftConfigFile->inputFileData.items() )
	{
		pSpacecraftArray[i] = new Spacecraft(spacecraftName, spacecraftConfig, pEarth);
		pIntegratorRK4->registerModel(pSpacecraftArray[i]);
		++i;
	}

	// build observers
	const std::size_t numObservers { pObserverConfigFile->inputFileData.size() };
	std::vector<Observer*> pObserverArray ( numObservers, nullptr );
	i = 0;
	for ( const auto& [observerName, observerConfig] : pObserverConfigFile->inputFileData.items() )
	{
		pObserverArray[i] = new Observer(observerName, observerConfig, pEarth);
		pIntegratorRK4->registerModel(pObserverArray[i]);
		for ( std::size_t k { 0 }; k < numSpacecraft; ++k )
		{
			pObserverArray[i]->registerSpacecraft(pSpacecraftArray[k]);
		}
		++i;
	}
	
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
	if (ERROR == pScheduler->getStatus())
	{
		printf("  Error: %s\n", pScheduler->getErrorMessage().c_str());
	}
	printf("--------------------------------\n");

	// clean up
	for ( std::size_t i { 0 }; i < numObservers; ++i )
	{
		delete pObserverArray[i];
	}
	for ( std::size_t i { 0 }; i < numSpacecraft; ++i )
	{
		delete pSpacecraftArray[i];
	}
	delete pIntegratorRK4;
	delete pScheduler;
	delete pEarth;
	delete pSimConfigFile;
	delete pSpacecraftConfigFile;
	delete pObserverConfigFile;
}
