/*
** ------------ Header Guard -------------
*/ 
#ifndef OUTPUTPRODUCER_HH  
#define OUTPUTPRODUCER_HH

/*
** ------- Preprocessor directives -------
*/ 
#include "Vector.hh"
#include <cstddef>  // for std::size_t
#include <fstream>  // for std::ofstream
#include <string>	// for std::string

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
	std::ofstream _outputFile;
	const std::string _outputFileName;

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
	void registerOutput(const std::string& variableName, const double& variable);
	void registerOutput(const std::string& variablename, const Vector3& variable);
	void registerOutput(const std::string& variableName, const Vector6& variable);
	void output(const double& integratorTime);

	// setter functions


};

#endif  // OUTPUTPRODUCER_HH
