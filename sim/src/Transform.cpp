/*
** ------- Preprocessor directives -------
*/ 
#include "Transform.hh"
#include "Matrix.hh"
#include <cmath>	// for std::sqrt(), std::acos(), etc.

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
Transform::Transform(const int variable) :
	_variable { variable }
{
	
}

const Matrix3 Transform::rot1(const double& theta)
{
	return Matrix3 {
		{ 1.0, 0.0, 0.0 },
		{ 0.0, std::cos(theta), std::sin(theta) },
		{ 0.0, -1.0 * std::sin(theta), std::cos(theta) }
	};
}

const Matrix3 Transform::rot2(const double& theta)
{
	return Matrix3 {
		{ std::cos(theta), 0.0,  -1.0 * std::sin(theta) },
		{ 0.0, 1.0, 0.0 },
		{ std::sin(theta), 0.0, std::cos(theta) }
	};
}

const Matrix3 Transform::rot3(const double& theta)
{
	return Matrix3 {
		{ std::cos(theta), std::sin(theta), 0.0 },
		{ -1.0 * std::sin(theta), std::cos(theta), 0.0 },
		{ 0.0, 0.0, 1.0 }
	};
}
