// ------- Preprocessor directives -------
#include "containers.h"	// best practice to include corresponding header (helps with catching errors)
#include <iostream>     // because we need std::cout, must include iostream here
#include <string>
#include <vector>
#include <array>
#include <iterator>		// for std::size()
#include <typeinfo>		// for typeid()
#include <cassert>
 
// containers provide storage for a collection of unnamed objects (called elements).
  // containers are homogeneous, meaning all elements must have the same data type
  // containers are most often implemented as template classes
  // strings are a type of container that store characters

// arrays are a type of container that allocate their elements contiguously in memory, and allow fast, direct access to any element via subscripting
  // C++ has three different array types that are commonly used: std::vector, std::array, and C-style arrays

// ------- Namespace directives -------
namespace Students
{
	enum Names : unsigned int  // explicitly specify unsigned int to prevent conversion issue to size_t
	{
		rick,	// 0
		morty,	// 1
		summer,	// 2
		beth,	// 3
		// future enumerators go here
		max_students  // 4, count enumerator
	};
}

template <typename T, std::size_t Row, std::size_t Col>
using Array2d = std::array<std::array<T, Col>, Row>;


// ------- User-Defined Functions -------

// vector function parameters must explicity list their type (templates are often used to get around this)
  // containers are usually passed by reference
template <typename T>
void vecPrintFor(const std::vector<T>& vec) 
{
	std::cout << "Vector: [";
	for ( std::size_t idx { 0 }; idx < vec.size(); ++idx )
    {
		std::cout << vec[idx];
		if ( idx < (vec.size() - 1) )
		{
			std::cout << ", ";
		}
    }
	std::cout << "]\n";
}

template <typename T>
void vecPrintForEach(const std::vector<T>& vec) 
{
	std::cout << "Vector: [";

	// for-each (or range-based) loops iterate through each element of an array
	  // safer than for loops (avoids indexing issues)
	  // most common for the element declaration to be passed by reference
	  // range-based loops work with arrays, vectors, linked lists, trees, and maps
	  // syntax: for (element_declaration : array)
	int count { 0 };
	for ( const auto& element : vec )  // can use T or auto here, best practice to use auto
    {
		std::cout << element;
		if ( count < (vec.size() - 1) )
		{
			std::cout << ", ";
			++count;
		}
			
    }
	std::cout << "]\n";
}

std::vector<int> initVec(const int size)
{
	std::vector<int> vec ( size );

	// vectors and strings support move semantics, meaning they are inexpensive to return by value
	  // i.e. data from temporary variable vec is moved instead of copied
	return vec;
}

template <typename T>
void vecPrintCapLen(const std::vector<T>& v)
{
	std::cout << "Capacity: " << v.capacity() << " Length: "	<< v.size() << '\n';
}

template <typename T>
void arrPrintFirstIdx(const T* arrPtr)
{
	// note that we have no knowledge of array's length here 
	  // for loops and functions std::size() won't work
	  // typical work around is to pass length as a second argument or including some kind of terminating element at the end of the array (e.g. -1 or null)
	std::cout << "Array first index: " << arrPtr[0] << '\n';
}

template <typename T>
void arrPrintSecondIdx(const T arrPtr[])  // parameters are equivalent to arrPrintFirstIdx but preferred
{
	// incrementing a pointer will return the address of the next object in memory
	  // based on the type of pointer (e.g. if int is 4 bytes then an int* ptr+1 jumps forward in memory 4 bytes)
	  // can also use ++ptr to modify the address stored by ptr
	  // ptr[n] = *(ptr + n)
	std::cout << "Array second index: " << *(arrPtr + 1) << '\n';
}

void vectorPractice()
{
	std::cout << "\nvectorPractice(): \n";

	std::vector<int> primes{ 2, 3, 5, 7 };
	std::vector vowels { 'a', 'e', 'i', 'o', 'u' };  // uses class template argument deduction to deduce type char
	std::vector<int> zeros ( 10 );  // creates a vector of size 10, must be done with direct initialization, i.e. parenthesis

	// C++ indexing is 0 based
	  // indexing is actually specifying an offset in memory from the first element of the array
	  // passing an invalid (out of bounds) index will return undefined behavior
	    // the at() member function performs bounds checking on the index
	  // arrays are contiguous, meaning their elements are adjacent in memory
	  // lengths and indices are type size_type (alias for size_t which is unsigned int)
	  // can use enumerations as a form of indexing
	std::size_t idx { 2 };
	std::cout << "An int is " << sizeof(int) << " bytes\n";
    std::cout << &(primes[0]) << '\n';
    std::cout << &(primes.at(1)) << '\n';
    std::cout << &(primes[idx]) << '\n';

	std::cout << "There are " << vowels.size() << " primary vowels\n";
	std::cout << "There are " << std::size(vowels) << " primary vowels\n";
	
	vecPrintFor(primes);
	vecPrintForEach(vowels);
	vecPrintFor(initVec(5));

	std::cout << "What prime number is Morty? " << primes[Students::morty] << '\n';
	assert(primes.size() == Students::max_students);

	// a vector's capacity is how many elements it has allocated
	  // unused elements can be used later without overflowing the vector
	// a vector's length is how many elements are currently being used
	  // indexing is always based on length, not capacity
	  // the empty() member function returns true if vector is 0-length

	// unlike arrays, vectors can be resized after being initiated, however, resizing (aka dynamic memory allocation) can be expensive
	// the process is as follows:
	  // The vector acquires new memory with capacity for the desired number of elements. These elements are value-initialized.
	  // The elements in the old memory are copied (or moved, if possible) into the new memory. The old memory is then returned to the system.
	  // The capacity and length of the vector are set to the new values.

	vecPrintCapLen(primes);  	// capacity and length are both 4
	primes.resize(6);  		// appends 2 new elements to the end of the vector (zero-initialized)
	vecPrintCapLen(primes);  	// dynamic memory allocation now allocates more than what is needed but length is 6
	vecPrintForEach(primes);
	primes.resize(2);  		// removes the last 4 elements of the vector 
	vecPrintCapLen(primes);	// shrinking a vector size only changes length, not capacity 
	vecPrintForEach(primes);
	primes.reserve(10); 	// reserve changes the capacity but not the length, only increases, won't decrease
	vecPrintCapLen(primes);

	// stack behavior is implemented in vectors using the following member functions
	primes.push_back(5);			// push -- adds element to the end of the vector, may cause reallocation if necessary
	primes.pop_back(); 				// pop -- removes element at the end of the vector, returns void
	int num { primes.back() };		// top / peek -- returns the element at the end of the vector but does not remove it

}


void arrayPractice()
{
	std::cout << "\narrayPractice(): \n";

	// typically only use std::array for constexpr arrays, and std::vector otherwise

	// std::array has two arguments: the element type and the array length
	  // the length argument must be a constexpr
	constexpr int len { 3 };
	std::array<int, 5> a {};
	std::array<int, len> b {};
	std::array<int, Students::max_students> c {};
	std::array d { 1.2, 1.5, 4.7 };  // let the compiler deduce type and size

	std::cout << "a has " << a.size() << " elements\n";
	std::cout << "b has " << std::size(b) << " elements\n";

	// std::array and c-style array indexing is the same as vectors


	// typically avoid c-style arrays in favor of std::array and std::vector

	// c-style arrays have one argument: the array length
	int e[10] {};  				// creates a c-style array with length 10
	int f[] { 1, 2, 3, 4, 5 };  // let the compiler deduce size
	int g[5] { 6, 7 }; 			// indices 0 and 1 are assigned, the rest are 0

	std::cout << "e has " << std::size(e) << " elements\n";

	// when a c-style array is used in an expression, it implicitly converts to a pointer to the first element address
	  // this is called array decay (or just decay) because you lose the length information
	  // you cannot pass a c-style array by reference, but you don't need to since it will always decay into a pointer
	auto ptr{ f }; 	// evaluation causes arr to decay, type deduction should deduce type int*
    std::cout << (typeid(ptr) == typeid(int*)) << '\n'; // prints true 
    std::cout << (&f[0] == ptr) << '\n';  				// prints true

	std::cout << "Standard Index: " << f[2] << "\nPointer Index: " << ptr[2] << '\n';

	arrPrintFirstIdx(f);
	arrPrintSecondIdx(f);

	// for loop using pointer arithmetic
	int* begin { f };				// get memory address of first element
	int* end { f + std::size(f) };	// get memory address of one past the last element
	for (; begin != end; ++begin)
	{
		std::cout << *(begin) << " ";
	}
	std::cout << '\n';

	// for-each loop only works because the size of f is known at compile time
	  // would not work inside a function if f is passed in since it would decay and lose length info
	for (auto element : f)
	{
		std::cout << element << ' ';
	}
	std::cout << '\n';

}

void multiDimPractice()
{
	std::cout << "\nmultiDimPractice(): \n";

	// std::array, std::vector, and c-style arrays can be multidimensional
	  // conceptually, the left subscript is the row and the right is the column
	  // in memory, elements are placed sequentially row by row
	  	// col 0    col 1    col 2    col 3    col 4
		// a[0][0]  a[0][1]  a[0][2]  a[0][3]  a[0][4]  row 0
		// a[1][0]  a[1][1]  a[1][2]  a[1][3]  a[1][4]  row 1
		// a[2][0]  a[2][1]  a[2][2]  a[2][3]  a[2][4]  row 2

	int empMat[3][3] {};
	int mat[3][3]  // only the left most index can be omitted
	{
		{ 1, 2, 3 }, 
		{ 4, 5 },		// missing initializers will be value-initialized (to 0)
		{ 7, 8, 9 }
	};
	
	// multidimensional std::arrays have "backwards" indices when defined
	std::array<std::array<int,4>,3> arr	// this is equivalent to int arr[3][4]
	{{  // note double bracers
		{ 1, 2, 3, 4 }, 
		{ 5, 6, 7, 8 },
		{ 9, 10, 11, 12 }
	}};

	// often use aliases / alias templates
	Array2d<int,3,4> arr2 { arr };

	// double for-loop with indices
    for (std::size_t row{0}; row < std::size(mat); ++row) // std::size(arr) returns the first dimension of the array (rows)
    {
        for (std::size_t col{0}; col < std::size(mat[0]); ++col) // std::size(arr[0]) returns the number of columns
            std::cout << mat[row][col] << ' ';

        std::cout << '\n';
    }

    // double range-based for-loop
    for (const auto& arow : arr)   // get each array row
    {
        for (const auto& e : arow) // get each element of the row
            std::cout << e << ' ';

        std::cout << '\n';
    }
}