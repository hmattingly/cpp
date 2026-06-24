
// ------- Header Guard -------
#ifndef VECTOR3_H  
#define VECTOR3_H

#include <cmath>
#include <cassert>

// ------- Class Definition -------
class Vector3
{
	public:
	double x { 0.0 }; // TODO alter this to be 3x1 vector
	double y { 0.0 };
	double z { 0.0 };

	// default constructor
	Vector3() = default;

	// constructor
	Vector3(double a, double b, double c)
		: x { a }, y { b }, z { c }
	{}

	// copy constructor
	Vector3(const Vector3& v)
		: x { v.x }, y { v.y }, z { v.z }
	{}

	double mag2() const
	{
		return x*x + y*y + z*z;
	}

	double mag() const
	{
		return std::sqrt(this->mag2());
	}

	Vector3 unit() const
	{
		double magnitude = this->mag();
		assert(magnitude != 0.0);	// cannot normalize a zero vector

		return Vector3 
		{ 
			x / magnitude, 
			y / magnitude, 
			z / magnitude 
		};
	}

	double dot(const Vector3& v) const
	{
		return x * v.x + y * v.y + z * v.z;
	}

	Vector3 cross(const Vector3& v) const
	{
		return Vector3
		{
			y * v.z - z * v.y,
			z * v.x - x * v.z,
			x * v.y - y * v.x
		};
	}

	Vector3 operator+(const Vector3& v) const
	{
		return Vector3
		{
			x + v.x,
			y + v.y,
			z + v.z
		};
	}

	Vector3 operator-(const Vector3& v) const
	{
		return Vector3
		{
			x - v.x,
			y - v.y,
			z - v.z
		};
	}

	Vector3 operator*(const double& scalar) const
	{
		return Vector3
		{
			x * scalar,
			y * scalar,
			z * scalar
		};
	}

	Vector3 operator/(const double& scalar) const
	{
		return Vector3
		{
			x / scalar,
			y / scalar,
			z / scalar
		};
	}

	Vector3& operator+=(const Vector3& v)
	{
		x += v.x;
		y += v.y;
		z += v.z;

		return *this;
	}

	Vector3& operator-=(const Vector3& v)
	{
		x -= v.x;
		y -= v.y;
		z -= v.z;

		return *this;
	}

	Vector3& operator*=(const double& scalar)
	{
		x *= scalar;
		y *= scalar;
		z *= scalar;

		return *this;
	}

	Vector3& operator/=(const double& scalar)
	{
		x /= scalar;
		y /= scalar;
		z /= scalar;

		return *this;
	}

	// TODO: add outer product function once Matrix3 class is implemented
};

#endif // VECTOR3_H
