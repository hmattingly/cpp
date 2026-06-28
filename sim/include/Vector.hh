
// ------- Header Guard -------
#ifndef VECTOR_HH 
#define VECTOR_HH

#include <ostream>
#include <cmath>
#include <cassert>
#include <array>
#include <cstddef>	// for std::size_t
#include "util.hh"

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

	Vector operator-() const
	{
		Vector result;
		for (std::size_t i = 0; i < N; ++i)
			result[i] = -_vec[i];
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

	bool operator==(const Vector& v) const
	{
		if ((*this - v).mag() < Util::FLOAT_TOL)
			return true;
		else
			return false;
	}

	bool operator!=(const Vector& v) const
	{
		return !(*this == v);
	}


	// member functions
	double mag2() const
	{
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
		assert(magnitude > Util::FLOAT_TOL);	// cannot normalize a zero vector

		return *this / magnitude;
	}

	bool isZero() const
	{
		return this->mag() < Util::FLOAT_TOL;
	}

	bool isUnit() const
	{
		return std::abs(this->mag() - 1.0) < Util::FLOAT_TOL;
	}


	// access functions
	const std::array<double, N>& data() const
	{
		return _vec;
	}
};

template <std::size_t N>
inline Vector<N> operator*(double scalar, const Vector<N>& v)
{
    return v * scalar;
}

template <std::size_t N>
inline double dot(const Vector<N>& a, const Vector<N>& b)
{
	double sum = 0;
	for (std::size_t i = 0; i < N; ++i)
	{
		sum += a[i] * b[i];
	}
	return sum;
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

template <std::size_t N>
inline double angleBetween(const Vector<N>& a, const Vector<N>& b)
{
	double mags = a.mag() * b.mag();
	assert(mags > Util::FLOAT_TOL);

	return std::acos(dot(a, b) / mags);
}


#endif // VECTOR_HH
