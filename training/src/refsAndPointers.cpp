// ------- Preprocessor directives -------
#include "refsAndPointers.h"
#include <iostream>
#include <string>
 
// ------- User-Defined Functions -------
// pass by reference
  // x is now a reference to whatever object is passed in (no copy is made)
void addOneReference(int& x) {  // note, this function will not accept a const or literal
	++x;
}

void printReference(const std::string& s) {  // prevents copying girthy objects
	std::cout << s << '\n';
}

int& returnReference() {  // typcially want to avoid returning reference to a non-const object
	static int x { 10 };  // use static so that the reference isn't hanging
	int& y { x };
	return y;
}

// pass by address
	// common use is to allow optional arguments
void addOneAddress(int* x) {
	++(*x);  // parentheses ensure we dereference before trying to increment
}

void printAddress(const std::string* s) {  // address passed in is copied to const string s
	std::cout << *s << '\n';
	s = nullptr;  // note that s is now a null pointer but that doesn't mean what is passed in becomes a null pointer
}

void addOneAddressOptArg(int* x=nullptr) {
	if (x)  // null pointers evaluate to false
		++*x;
	else
		std::cout << "No object to increment" << '\n';
}

void passByAddressAndReference(int*& x) {  // pass in a pointer by reference if you want to modify the address it points to
	x = nullptr;  // now whatever we passed in becomes a null pointer
}

// favor references over pointers
	// only advantage of pointers is they can be reassigned to a different memory location
void referencePractice() {
	// lvalue references are used to link an identifier to the same memory location as an object st changing the reference also changes the object (and vice versa)
		// the type of a reference determines what type of object it can refer to
		// lvalue references use since &. e.g. int&, double&.
		// non-const lvalue references can only bind to modifiable lvalues
		// const lvalue references can bind to modifiable lvalues, non-modifiable lvalues, and rvalues
		// references must be initialized when declared
		// references cannot change to reference a new object
	int a { 5 };
	int& b { a };  // b is an lvalue reference that can serve as an alias for a
	int& c { b };  // c is an lvalue reference to a, not a reference to a reference

	b = 6;  // now a = 6

	// you do not need to forward declare child functions in header files
	addOneReference(b);  // now a = b = c = 7
	printReference("\nReference Test");

	std::cout << "Value of a: " << a << '\n';

	const int d { 5 };
	const int& e { d };  // e is a const lvalue reference
		// cannot bind a non-const lvalue reference to a const (e.g. int& f { d };)
	const int& f { 5 };  // creates a temporary variable to hold the literal 5 then binds to it
		// cannot bind a non-const lvalue reference to an rvalue (e.g. int& f { 5 };)

	// & also serves as the "address of" operator
	std::cout << "Address of a: " << &a << '\n';  // prints the hex memory address of a

	int& g { returnReference() };  // g is a reference to the value of x in returnReference()
	auto h { b };                  // auto drops references, so h is now a copy of b
	auto& i { b };                 // i is a reference to b
}

void pointerPractice() {
	// pointers are an object that holds the memory address of another object
		// pointers should always be intialized when declared (otherwise get a garbage address)
		// pointers must always be initialized with a memory address (e.g. &x)
		// non-const pointers can only point to modifiable object addresses
		// the size of every pointer is the same given the size of a memory address is constant
	int a { 5 };
	int z { 6 };
	int* b { &a };  // b is a pointer to the memory address of a
	int* c {};      // null pointer, not holding an address
	int* d { nullptr };  // same as above

	// * also serves as the dereference operator used to access the value stored at a memory address. It is the opposite of &
	std::cout << "\nAddress of a: " << b << '\n';
	std::cout << "Value of a: " << *(b) << '\n';

	// can alter the value stored at a memory address by derefercing the pointer
	*b = 6;  // dereference returns an lvalue

	std::string s { "Address Test" };
	addOneAddress(b);  // now a = 7
	printAddress(&s);

	std::cout << "Value of a: " << a << '\n';

	// non-const pointers can be reassigned to new memory addresses
	b = &z;  // b now points to the memory address of z

	const int e { 5 };
	const int* f { &e };           // f is a pointer to the constant variable e
	const int* g { &a };           // g is a pointer to a "const int". now *g = 6 is invalid but a = 6 is valid
	int* const h { &a };           // h is a constant pointer to the non-const variable a. now g = &z is invalid but *g = 6 is valid
	const int* const i { &e };     // i is a constant pointer to the constant variable e. now h = &z is invalid and *h = 6 is invalid
	
	addOneAddressOptArg();         // function does nothing
	addOneAddressOptArg(b);        // now a = 8
	passByAddressAndReference(b);  // now b is a null pointer

	if (b)
		std::cout << "b is not null\n";
	else
		std::cout << "b is null\n";

	auto j { f };  // auto does not drop pointers, so j is a pointer to e
}
 
