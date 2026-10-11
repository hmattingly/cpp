/*
** ------------ Header Guard -------------
*/ 
#ifndef OUTPUTPRODUCER_HH  
#define OUTPUTPRODUCER_HH

/*
** ------- Preprocessor directives -------
*/ 
#include "Vector.hh"
#include <string>   // for string
#include <cstddef>  // for std::size_t
#include <fstream>  // for std::ofstream

/*
** -------------- Constants ---------------
*/ 
inline constexpr int MAX_OUTVARS { 2048 };	// max number of output variables per integrator


/*
** -------- Forward Declarations ----------
*/ 

/*
** --------- Namespace directives ---------
*/ 

/*
** ----------- Class Definition ------------
*/ 
struct OutputVariable
{
	std::string name { "no_name" };
	const double* value { nullptr };
};

/*
** ----------- Class Definition ------------
*/ 
class OutputProducer
{
protected:
	std::ofstream _outputFile { NULL };
	std::string _outputFileName;

	OutputVariable _outputVars[MAX_OUTVARS] {};
	std::size_t _numOutVars { 0 };

public:
	// default constructor (disabled)
	OutputProducer() = delete;

	// parameterized constructor
	OutputProducer(const std::string& pFileName);

	// destructor
	~OutputProducer() = default;

	// forward declarations
	void registerOutput(const std::string& pVariableName, const double& variable);
	void registerOutput(const std::string& pVariablename, const Vector3& variable);
	void output(const double& integratorTime);

	// setter functions
	void setOutputFileName(const std::string& pFileName) { _outputFileName = pFileName; }

};

#endif  // OUTPUTPRODUCER_HH
