/*
** ------------ Header Guard -------------
*/ 
#ifndef TRANSFORM_HH  
#define TRANSFORM_HH

/*
** ------- Preprocessor directives -------
*/ 
#include "Matrix.hh"


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
class Transform
{
private:
	Matrix3 _mat { IDENTITY_MATRIX3 };

public:
	// default constructor (disabled)
	Transform();

	// destructor
	~Transform() = default;

	// forward declarations
	static const Matrix3 rot1(const double& theta);
	static const Matrix3 rot2(const double& theta);
	static const Matrix3 rot3(const double& theta);

	// access functions

	// setter functions

};

#endif  // TRANSFORM_HH
