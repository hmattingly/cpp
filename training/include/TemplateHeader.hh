/*
** ------------ Header Guard -------------
*/ 
#ifndef TEMPLATE_HH  
#define TEMPLATE_HH

/*
** ------- Preprocessor directives -------
*/ 

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
class Template
{
private:
	int _variable { 0 };

public:
	// default constructor (disabled)
	Template() = delete;

	// parameterized constructor
	Template(const int variable);

	// destructor
	~Template() = default;

	// forward declarations

	// access functions

	// setter functions

};

#endif  // TEMPLATE_HH
