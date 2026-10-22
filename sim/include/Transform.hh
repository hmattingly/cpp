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

public:
	// default constructor
	Transform();

	// destructor
	~Transform() = default;

	// forward declarations
	static const Matrix3 rot1(const double& theta);
	static const Matrix3 rot2(const double& theta);
	static const Matrix3 rot3(const double& theta);
	static const Matrix3 lvlh2eci(const double& inc, const double& rann, const double& aol);
	static const Matrix3 eci2lvlh(const double& inc, const double& rann, const double& aol);
	static const Vector6 eci2kep(const Vector3& r, const Vector3& v);

	// access functions
	

	// setter functions

};

#endif  // TRANSFORM_HH
