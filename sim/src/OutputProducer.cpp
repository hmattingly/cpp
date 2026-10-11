/*
** ------- Preprocessor directives -------
*/ 
#include "OutputProducer.hh"
#include <string>   // for string

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
** ----------- Class Definition ------------
*/ 
// constructor
OutputProducer::OutputProducer(const std::string& pFileName) :
	_outputFileName { pFileName }
{

}

// register output variables to be outputted to csv
void OutputProducer::registerOutput(const std::string& variableName, const double& variable)
{
	// check if the max number of output variables has been reached
	if ( _numOutVars >= MAX_OUTVARS )
	{
		printf("Error: Maximum number of output variables exceeded!\n");
		std::exit(EXIT_FAILURE);
	}

	// check if the output variable has already been set
	for (std::size_t i { 0 }; i < _numOutVars; ++i)
	{
		if ( variableName == _outputVars[i].name )
		{
			printf("Error: Variable name %s already registered to output!\n", variableName.c_str());
			std::exit(EXIT_FAILURE);
		}
		else if ( &variable == _outputVars[i].value )
		{
			printf("Error: Variable value for %s already registered to output!\n", variableName.c_str());
			std::exit(EXIT_FAILURE);
		}
	}
	_outputVars[_numOutVars] = { variableName, &variable };
	++_numOutVars;
}

// register output variables to be outputted to csv (overload for Vector3)
void OutputProducer::registerOutput(const std::string& variableName, const Vector3& variable)
{
	// add vectors to output, rename with _1, _2, and _3
	for ( int i { 0 }; i < 3; ++i )
	{
		std::string newVariableName = variableName + "_" + std::to_string(i + 1);
        registerOutput(newVariableName, variable[i]);
	}
}

void OutputProducer::output(const double& integratorTime)
{
	// open the file if not already open and write headers
    if ( false == _outputFile.is_open() )
    {
        _outputFile.open(_outputFileName);

		// check if file opened successfully
		if ( false == _outputFile.is_open() )
		{
			printf("Error: Failed to open %s", _outputFileName.c_str());
			std::exit(EXIT_FAILURE);
		}

		// write header row
		_outputFile << "Time";

		for ( std::size_t i { 0 }; i < _numOutVars; ++i )
		{
			_outputFile << "," << _outputVars[i].name;
		}

		// move to new row
		_outputFile << "\n";
    }
	
	// loop through each variable and output to file
	_outputFile << integratorTime;
	for ( std::size_t i { 0 }; i < _numOutVars; ++i )
	{
		_outputFile << "," << *(_outputVars[i].value);
	}

	// move to new row
	_outputFile << "\n";
	
	// flush output to file
	_outputFile.flush();
}
