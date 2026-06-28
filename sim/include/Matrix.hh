
// ------- Header Guard -------
#ifndef MATRIX_HH 
#define MATRIX_HH

#include <ostream>
#include <cmath>
#include <cassert>
#include <array>
#include <cstddef>	// for std::size_t
#include "Vector.hh"
#include "util.hh"

// ------- Forward Declarations -------
template <std::size_t ROWS, std::size_t COLS>
class Matrix;

// ------- Type Aliases -------
using Matrix3 = Matrix<3, 3>;
using Matrix2 = Matrix<2, 2>;
using Matrix6 = Matrix<6, 6>;

// ------- Class Definition -------
template <std::size_t ROWS, std::size_t COLS>
class Matrix
{
	std::array<Vector<COLS>, ROWS> _mat {};

public:
	
	// default constructor
	Matrix() = default;

	// copy constructor
	Matrix(const Matrix<ROWS, COLS>&) = default;

	// constructor with initializer list
	Matrix(std::initializer_list<Vector<COLS>> rows)
	{
		assert(rows.size() == ROWS);
		std::size_t i = 0;
		for (const Vector<COLS>& v : rows)
		{
			_mat[i++] = v;
		}
	}

	// operator overloads
	Vector<COLS>& operator[](std::size_t i)
	{
		assert(i < ROWS);
        return _mat[i];
	}

    const Vector<COLS>& operator[](std::size_t i) const 
	{
        assert(i < ROWS);
        return _mat[i];
    }

	Matrix operator+(const Matrix& m) const
	{
		// assert that the dimensions of the two matrices are the same?
		Matrix result;
		for (std::size_t i = 0; i < ROWS; ++i)
		{
			result[i] = _mat[i] + m[i];
		}
		return result;
	}

	Matrix operator-(const Matrix& m) const
	{
		// assert that the dimensions of the two matrices are the same?
		Matrix result;
		for (std::size_t i = 0; i < ROWS; ++i)
		{
			result[i] = _mat[i] - m[i];
		}
		return result;
	}

	Matrix operator-() const
	{
		Matrix result;
		for (std::size_t i = 0; i < ROWS; ++i)
		{
			result[i] = -_mat[i];
		}
		return result;
	}

	Matrix operator*(double scalar) const
	{
		Matrix result;
		for (std::size_t i = 0; i < ROWS; ++i)
		{
			result[i] = _mat[i] * scalar;
		}
		return result;
	}

	Vector<ROWS> operator*(const Vector<COLS>& v) const
	{
		Vector<ROWS> result;
		for (std::size_t i = 0; i < ROWS; ++i)
		{
			result[i] = dot(_mat[i], v);
		}
		return result;
	}

	template <std::size_t K>
	Matrix<ROWS, K> operator*(const Matrix<COLS, K>& m) const
	{
		Matrix<ROWS, K> result;
		for (std::size_t i = 0; i < ROWS; ++i)
		{
			for (std::size_t j = 0; j < K; ++j)
			{
				double sum = 0.0;
				for (std::size_t k = 0; k < COLS; ++k)
				{
					sum += _mat[i][k] * m[k][j];
				}
				result[i][j] = sum;
			}
		}
		return result;
	}

	Matrix operator/(double scalar) const
	{
		assert(scalar != 0);
		Matrix result;
		for (std::size_t i = 0; i < ROWS; ++i)
		{
			result[i] = _mat[i] / scalar;
		}
		return result;
	}

	Matrix& operator+=(const Matrix& m)
	{
		for (std::size_t i = 0; i < ROWS; ++i)
		{
			_mat[i] += m[i];
		}
		return *this;
	}

	Matrix& operator-=(const Matrix& m)
	{
		for (std::size_t i = 0; i < ROWS; ++i)
		{
			_mat[i] -= m[i];
		}
		return *this;
	}

	Matrix& operator*=(double scalar)
	{
		for (std::size_t i = 0; i < ROWS; ++i)
		{
			_mat[i] *= scalar;
		}
		return *this;
	}

	Matrix& operator/=(double scalar)
	{
		assert(scalar != 0);
		for (std::size_t i = 0; i < ROWS; ++i)
		{
			_mat[i] /= scalar;
		}
		return *this;
	}

	bool operator==(const Matrix& m) const
	{
		for (std::size_t i = 0; i < ROWS; ++i)
		{
			if ((_mat[i] != m[i]))
				return false;
		}
		return true;
	}

	bool operator!=(const Matrix& m) const
	{
		return !(*this == m);
	}

	friend std::ostream& operator<<(std::ostream& os, const Matrix& m)
	{
		os << "[\n";
		for (std::size_t i = 0; i < ROWS; ++i)
		{
			os << "  " << m[i];
			if (i < ROWS - 1)
				os << ",";
			os << "\n";
		}
		os << "]";
		return os;
	}

	// member functions
	double trace() const
	{
		static_assert(ROWS == COLS);
		double sum = 0.0;
		for (std::size_t i = 0; i < ROWS; ++i)
		{
			sum += _mat[i][i];
		}
		return sum;
	}

	Matrix<COLS, ROWS> transpose() const
	{
		Matrix<COLS, ROWS> result;
		for (std::size_t i = 0; i < ROWS; ++i)
		{
			for (std::size_t j = 0; j < COLS; ++j)
			{
				result[j][i] = _mat[i][j];
			}
		}
		return result;
	}

	double frobeniusNorm() const
	{
		double sum = 0.0;
		for (std::size_t i = 0; i < ROWS; ++i)
		{
			for (std::size_t j = 0; j < COLS; ++j)
			{
				sum += _mat[i][j] * _mat[i][j];
			}
		}
		return std::sqrt(sum);
	}

	double determinant() const
	{
		static_assert(ROWS == COLS,	"Determinant is only defined for square matrices.");

		if constexpr (ROWS == 2)
		{
			return	_mat[0][0] * _mat[1][1]	- _mat[0][1] * _mat[1][0];
		}
		else if constexpr (ROWS == 3)
		{
			return
				_mat[0][0] * (_mat[1][1] * _mat[2][2] - _mat[1][2] * _mat[2][1])
				- _mat[0][1] * (_mat[1][0] * _mat[2][2] - _mat[1][2] * _mat[2][0])
				+ _mat[0][2] * (_mat[1][0] * _mat[2][1] - _mat[1][1] * _mat[2][0]);
		}
		else
		{
			static_assert(ROWS <= 3, "Determinant not implemented for this size.");
			return 0.0;	// placeholder
		}
	}

	// TODO: Implement inverse() function for 2x2, 3x3, and 6x6 matrices

	bool isSymmetric() const
	{
		static_assert(ROWS == COLS,	"Symmetry is only defined for square matrices.");

		for (std::size_t i = 0; i < ROWS; ++i)
		{
			for (std::size_t j = i + 1; j < COLS; ++j)
			{
				if (std::abs(_mat[i][j] - _mat[j][i]) > Util::FLOAT_TOL)
				{
					return false;
				}
			}
		}
		return true;
	}

	bool isIdentity() const
	{
		static_assert(ROWS == COLS);

		for (std::size_t i = 0; i < ROWS; ++i)
		{
			for (std::size_t j = 0; j < COLS; ++j)
			{
				double expected = (i == j) ? 1.0 : 0.0;
				if (std::abs(_mat[i][j] - expected) > Util::FLOAT_TOL)
				{
					return false;
				}
			}
		}
		return true;
	}

	bool isOrthogonal() const
	{
		static_assert(ROWS == COLS);

		return (this->transpose() * (*this)).isIdentity();
	}

	// access functions
	const std::array<Vector<COLS>, ROWS>& data() const
	{
		return _mat;
	}
};

template <std::size_t ROWS, std::size_t COLS>
inline Matrix<ROWS, COLS> operator*(double scalar, const Matrix<ROWS, COLS>& m)
{
    return m * scalar;
}

template <std::size_t N>
inline Matrix<N,N> identity()
{
    Matrix<N,N> I;
    for (std::size_t i = 0; i < N; ++i)
        I[i][i] = 1.0;
    return I;
}

template <std::size_t ROWS, std::size_t COLS>
inline Matrix<ROWS, COLS> outer(const Vector<ROWS>& u, const Vector<COLS>& v)
{
	Matrix<ROWS, COLS> result;
	for (std::size_t i = 0; i < ROWS; ++i)
	{
		for (std::size_t j = 0; j < COLS; ++j)
		{
			result[i][j] = u[i] * v[j];
		}
	}
	return result;
}

template <typename T, std::size_t N>
inline Matrix<N,N> diag(const std::array<T,N>& d)
{
    Matrix<N,N> result;
    for (std::size_t i = 0; i < N; ++i)
        result[i][i] = d[i];
    return result;
}

inline Matrix3 skew(const Vector3& v)
{
	return Matrix3{
		{  0.0, -v[2],  v[1] },
		{  v[2],  0.0, -v[0] },
		{ -v[1],  v[0], 0.0 }
	};
}

#endif // MATRIX_HH
