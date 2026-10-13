/*
** ------- Preprocessor directives -------
*/ 
#include "InputParser.hh"
#include <json.hpp>	// for json
#include <string>	// for string
#include <fstream>  // for std::ifstream
#include <iostream>	// for std::cout
#include <cstdio>	// for printf
#include <filesystem>  	// for std::filesystem
#include <cstddef>  // for std::size_t

/*
** -------------- Constants ---------------
*/ 

/*
** -------- Forward Declarations ----------
*/ 

/*
** --------- Namespace directives ---------
*/ 
using json = nlohmann::json;

/*
** ----------- Class Definition ------------
*/ 
InputParser::InputParser(const std::string& inputFileName) :
	_inputFileName { inputFileName }
{
	std::ifstream inputFile;

	if ( false == inputFile.is_open() )
    {
        inputFile.open("inputs/" + _inputFileName);

		// check if file opened successfully
		if ( false == inputFile.is_open() )
		{
			printf("Error: Failed to open %s", _inputFileName.c_str());
			std::exit(EXIT_FAILURE);
		}

		// parse using json library
		json jsonFile { json::parse(inputFile) };

		// // display inputs
		// printf("Importing Sim parameters from %s%s%s\n", std::filesystem::current_path().c_str(), "/inputs/", _inputFileName.c_str());
		// for (json::iterator itr { jsonFile.begin() }; itr != jsonFile.end(); ++itr) 
		// {
		// 	std::cout << "  " << itr.key() << " : " << itr.value() << "\n";
		// }
		// printf("--------------------------------\n");

		// // get sim time parameters
		// _inputFileData.simStartTime = jsonFile["simStartTime"].get<double>();
		// _inputFileData.simEndTime = jsonFile["simEndTime"].get<double>();
		// _inputFileData.timeStep = jsonFile["timeStep"].get<double>();

		// // get spacecraft initial state
		// for ( std::size_t i { 0 }; i < 3; ++i )
		// {
		// 	_inputFileData.RofBwrtOexpECI[i] = jsonFile["initialState"]["position"][i].get<double>();
		// 	_inputFileData.VofBwrtOexpECI[i] = jsonFile["initialState"]["velocity"][i].get<double>();
		// }
		
    }

}
