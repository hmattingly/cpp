/*
** ------------ Header Guard -------------
*/ 
#ifndef INPUTPARSER_HH  
#define INPUTPARSER_HH

/*
** ------- Preprocessor directives -------
*/ 
#include "Vector.hh"
#include <string>	// for string

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
** ----------- Struct Definition -----------
*/ 
struct InputData
{
	double simStartTime { 0.0 };
	double simEndTime { 0.0 };
	double timeStep { 0.0 };
	Vector3 RofBwrtOexpECI { 0.0, 0.0, 0.0 };
	Vector3 VofBwrtOexpECI { 0.0, 0.0, 0.0 };
};

/*
** ----------- Class Definition ------------
*/ 
class InputParser
{
private:
	std::string _inputFileName;
	InputData _inputFileData;

public:
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
