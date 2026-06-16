// ------- Preprocessor directives -------
#include "containers.h" // best practice to include corresponding header (helps with catching errors)
#include <iostream>     // because we need std::cout, must include iostream here
 

 
// ------- Namespace directives -------

 
// ------- User-Defined Functions -------

void memoryPractice()
{
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

}
