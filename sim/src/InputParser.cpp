/*
** ------- Preprocessor directives -------
*/ 
#include "InputParser.hh"
#include <json.hpp>		// for json
#include <string>		// for string
#include <fstream>  	// for std::ifstream
#include <iostream>		// for std::cout
#include <filesystem>  	// for std::filesystem
#include <cstdlib>  	// for std::exit()

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
		inputFileData = json::parse(inputFile);

		// display inputs
		std::cout << "Importing parameters from " << std::filesystem::current_path().c_str() << "/inputs/" << _inputFileName << "\n";
		for (json::iterator itr { inputFileData.begin() }; itr != inputFileData.end(); ++itr) 
		{
			std::cout << "  " << itr.key() << " : " << itr.value() << "\n";
		}
		std::cout << "--------------------------------\n";
    }
	else
	{
		std::cout << "Error: Unable to read from " << std::filesystem::current_path().c_str() << "/inputs/" << _inputFileName << "\n";
		std::exit(EXIT_FAILURE);
	}

}
