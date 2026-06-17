// ------- Preprocessor directives -------
#include "containers.h" // best practice to include corresponding header (helps with catching errors)
#include <iostream>     // because we need std::cout, must include iostream here
 
// ------- Namespace directives -------

// ------- User-Defined Functions -------

void memoryPractice()
{
	std::cout << "\nmemoryPractice(): \n";

	// unlike static or automatic memory, the program is responsible for requesting and disposing dynamically allocated memory
	  // dynamically allocated memory persists until freed with delete operator or the program ends

	// use the new operator to dynamically allocate memory for a data type on the heap
	  // the new operator returns a pointer containing the address of the memory that has been allocated
	  // accessing heap-allocated objects is generally slower than accessing stack-allocated objects
	int* ptr1 { new int };
	*ptr1 = 7;	// dereference the pointer to assign a value to it
	int* ptr2 { new int (5) };
	int* ptr3 { new int {6} };

	
	// use the delete operator to free the dynamically allocated memory for reuse
	  // it is good practice to set the pointer to null
	  // a memory leak occurs when a dynamically allocated variable is not deleted and pointer goes out of scope or is reassigned
	delete ptr1;
	delete ptr2;
	delete ptr3;
	ptr1 = nullptr;
	ptr2 = nullptr;
	ptr3 = nullptr;

	// create and destroy a dynamically allocated array using new[] and delete[]
	  // a dynamic array functions very similarly to a decayed array
	  // dynamically allocating an array allows you to set the array length at the time of allocation
	  // however, C++ does not provide a built-in way to resize an array that has already been allocated, use std::vector for this
	std::size_t len {};
	std::cout << "Enter an array length: ";
	std::cin >> len;
	int* arrPtr1 { new int[len] {} };  // arr is a pointer to an empty integer array of user specified length
	auto* arrPtr2 { new int[5] { 9, 7, 5, 3, 1 } };

	delete[] arrPtr1;
	delete[] arrPtr2;
	arrPtr1 = nullptr;
	arrPtr2 = nullptr;

	// we can use a pointer to an array of pointer to dynamically allocate a multidimensional array
	std::size_t numRows {};
	std::size_t numCols {};
	std::cout << "Enter a number of rows: ";
	std::cin >> numRows;
	std::cout << "Enter a number of columns: ";
	std::cin >> numCols;
	auto** arrPtr3 { new double*[numRows] }; // allocate an array of pointers — these are our rows
	for (int count { 0 }; count < static_cast<int>(numRows); ++count)
		arrPtr3[count] = new double[numCols] {}; // these are our columns

	for (int count { 0 }; count < static_cast<int>(numRows); ++count)
    	delete[] arrPtr3[count];
	delete[] arrPtr3; // this needs to be done last

	// see Classes.cpp destructors as well
}