/*
** ------------ Header Guard -------------
*/ 
#ifndef INPUTPARSER_HH  
#define INPUTPARSER_HH

/*
** ------- Preprocessor directives -------
*/ 
#include <json.hpp>		// for json
#include <string>		// for std::string

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
class InputParser
{
private:
	const std::string _inputFileName;

public:

	json inputFileData;

	// default constructor (disabled)
	InputParser() = delete;

	// parameterized constructor
	InputParser(const std::string& inputFileName);

	// destructor
	~InputParser() = default;

	// forward declarations

	// access functions

	// setter functions

};

#endif  // INPUTPARSER_HH
