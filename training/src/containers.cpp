// ------- Preprocessor directives -------
#include "containers.h"	// best practice to include corresponding header (helps with catching errors)
#include <iostream>     // because we need std::cout, must include iostream here
#include <string>
#include <vector>
#include <assert>
 
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


// ------- User-Defined Functions -------

// vector function parameters must explicity list their type (templates are often used to get around this)
  // containers are usually passed by reference
template <typename T>
void printFor(const std::vector<T>& vec) 
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
void printForEach(const std::vector<T>& vec) 
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

std::vector<int> initVector(const int size)
{
	std::vector<int> vec ( size );

	// vectors and strings support move semantics, meaning they are inexpensive to return by value
	  // i.e. data from temporary variable vec is moved instead of copied
	return vec;
}

void containerPractice()
{
	// containers are homogeneous, meaning all elements must have the same data type
	  // containers are most often implemented as template classes

	// strings are a type of container that store characters
	std::string hunter { "Hunter" };

	// vectors
	std::vector<int> primes{ 2, 3, 5, 7 };
	std::vector vowels { 'a', 'e', 'i', 'o', 'u' };  // uses class template argument deduction to deduce type char
	std::vector<int> zeros ( 10 );  // creates a vector of size 10, must be done with direct initialization

	// C++ indexing is 0 based
	  // indexing is actually specifying an offset in memory from the first element of the array
	  // passing an invalid (out of bounds) index will return undefined behavior
	    // the at() member function performs bounds checking on the index
	  // arrays are contiguous, meaning they are adjacent in memory
	  // lengths and indices are type size_type (alias for size_t which is unsigned int)
	  // can use enumerations as a form of indexing
	std::size_t idx { 2 };
	std::cout << "\nAn int is " << sizeof(int) << " bytes\n";
    std::cout << &(primes[0]) << '\n';
    std::cout << &(primes.at(1)) << '\n';
    std::cout << &(primes[idx]) << '\n';

	std::cout << "There are " << vowels.size() << " primary vowels\n";
	std::cout << "There are " << std::size(vowels) << " primary vowels\n";
	
	printFor(primes);
	printForEach(vowels);
	printFor(initVector(5));

	std::cout << "What prime number is Morty? " << primes[Students::morty] << '\n';
	assert(primes.size() == Students::max_students);

}
