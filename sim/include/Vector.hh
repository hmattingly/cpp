
// ------- Header Guard -------
#ifndef VECTOR_HH 
#define VECTOR_HH

#include <ostream>
#include <cmath>
#include <cassert>
#include <array>
#include <cstddef>	// for std::size_t

// ------- Forward Declarations -------
template <std::size_t N>
class Vector;

// ------- Type Aliases -------
using Vector3 = Vector<3>;
using Vector2 = Vector<2>;
using Vector6 = Vector<6>;

// ------- Class Definition -------
template <std::size_t N>
class Vector
{
	std::array<double, N> _vec {};

public:
	
	// default constructor
	Vector() = default;

	// copy constructor
	Vector(const Vector<N>&) = default;

	// constructor with initializer list
	Vector(std::initializer_list<double> values)
	{
		assert(values.size() == N);
		std::size_t i = 0;
		for (double x : values)
		{
			_vec[i++] = x;
		}
	}

	// operator overloads
	double& operator[](std::size_t i)
	{
		assert(i < N);
        return _vec[i];
	}

    const double& operator[](std::size_t i) const 
	{
        assert(i < N);
        return _vec[i];
    }

	Vector operator+(const Vector& v) const
	{
		Vector result;
		for (std::size_t i = 0; i < N; ++i)
		{
			result[i] = _vec[i] + v[i];
		}
		return result;
	}

	Vector operator-(const Vector& v) const
	{
		Vector result;
		for (std::size_t i = 0; i < N; ++i)
		{
			result[i] = _vec[i] - v[i];
		}
		return result;
	}

	Vector operator*(double scalar) const
	{
		Vector result;
		for (std::size_t i = 0; i < N; ++i)
		{
			result[i] = _vec[i] * scalar;
		}
		return result;
	}

	Vector operator/(double scalar) const
	{
		assert(scalar != 0);
		Vector result;
		for (std::size_t i = 0; i < N; ++i)
		{
			result[i] = _vec[i] / scalar;
		}
		return result;
	}

	Vector& operator+=(const Vector& v)
	{
		for (std::size_t i = 0; i < N; ++i)
		{
			_vec[i] += v[i];
		}
		return *this;
	}

	Vector& operator-=(const Vector& v)
	{
		for (std::size_t i = 0; i < N; ++i)
		{
			_vec[i] -= v[i];
		}
		return *this;
	}

	Vector& operator*=(double scalar)
	{
		for (std::size_t i = 0; i < N; ++i)
		{
			_vec[i] *= scalar;
		}
		return *this;
	}

	Vector& operator/=(double scalar)
	{
		assert(scalar != 0);
		for (std::size_t i = 0; i < N; ++i)
		{
			_vec[i] /= scalar;
		}
		return *this;
	}


	// member functions
	double mag2() const
	{
		assert(N <= 3);
		double sum = 0;
		for (std::size_t i = 0; i < N; ++i)
		{
			sum += _vec[i] * _vec[i];
		}
		return sum;
	}

	double mag() const
	{
		return std::sqrt(this->mag2());
	}

	Vector unit() const
	{
		double magnitude = this->mag();
		assert(magnitude > 1e-12);	// cannot normalize a zero vector

		return *this / magnitude;
	}

	
	// TODO: add outer product function once Matrix3 class is implemented

	// access functions
	const std::array<double, N>& vec() const
	{
		return _vec;
	}

	
};

inline double dot(const Vector3& a, const Vector3& b)
{
	return a[0] * b[0] + a[1] * b[1] + a[2] * b[2];
}

inline Vector3 cross(const Vector3& a, const Vector3& b) 
{
	return Vector3
	{
		a[1] * b[2] - a[2] * b[1],
		a[2] * b[0] - a[0] * b[2],
		a[0] * b[1] - a[1] * b[0]
	};
}


#endif // VECTOR_HH
