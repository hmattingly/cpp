// ------- Preprocessor directives -------
#include "functionPointers.h" // best practice to include corresponding header (helps with catching errors)
#include <iostream>     // because we need std::cout, must include iostream here
 
// ------- Namespace directives -------

// ------- User-Defined Functions -------
int returnZero()  // code for returnZero starts at memory address 0x61fdd8
{
	return 0;
}

int returnOne() { return 1; }

double add(double x, double y) { return x + y;}
double subtract(double x, double y) { return x - y; }
// mathFunc is a pointer to function specified as a parameter
  // can alternatively be written as double mathFunc(double, double)
  // supports default function pointers
double math(double x, double y, double (*mathFunc)(double, double) = subtract)
{
	double z = mathFunc(x, y);
	return z;
}

void functionPractice()  // code for returnOne starts at memory address 0x61fdd0
{
	std::cout << "\nfunctionPractice():\n";

	// function pointers hold the address to a function
	  // the syntax for a non-const function pointer is one of the ugliest things you will see in C++
	  // a function name with no paretheses, called a function identifier, decays to a pointer to that function
	  // the following pointers are for a function that has no parameters and returns an int
	  // the paretheses around *fncPtr are necessary
	int (*returnZeroPtr)();
	returnZeroPtr = returnZero;				// alternatively can be written as returnZeroPtr = &returnZero (which is more explicit)
	int (*returnOnePtr1)() { &returnOne };	// int (*returnOnePtr)() { returnOne } may be allowed by some compilers but not preferred
	auto returnOnePtr2 { &returnOne };		// alternate way of writing the above
	std::cout << "returnZero() is located at: " << &returnZeroPtr << '\n';
	std::cout << "returnOne() is located at: " << &returnOnePtr1 << '\n';

	// you can call a function from its pointer via explicit or implicit dereference
	  // default arguments are not resolved when a function is called through a function pointer
	int zero = (*returnZeroPtr)();	// explicit dereference
	int one = returnOnePtr1();		// implicit dereference (preferred)

	// function pointers can be passed as arguments to another function
	double z = math(4, 10, add);
	std::cout << "4 + 10 = " << z << '\n';
}
