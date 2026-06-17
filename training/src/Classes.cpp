// ------- Preprocessor directives -------
#include "classes.h"    // best practice to include corresponding header (helps with catching errors)
#include <iostream>     // because we need std::cout, must include iostream here
#include <string>
#include <cassert>      // for assert
 
// ------- Namespace directives -------
using namespace std::literals::string_literals;


// we can use the following compound data types to create user-defined types
  // Enumerations (scoped and unscoped)
  // Classes (structs, classes, and unions)
 
// Define user-defined types in the global scope so they can be used anywhere within this file (optional)
  // more common to put the user-defined type in its own header file (e.g. Scheduler.h)
 
// Classes
class Employee
{
// class members are private by default, meaning they can only be accessed by their own data members
  // this is literally the only difference between classes and structs
  // best practice is class members should only be private or protected data members but can and should have public member functions
  // private class member variables often prefixed with m_
    std::string m_firstName { "Blank" };
    double m_salary { 0.0 };
	
public:  // access specifier
   
    // constructors are special member functions that are automatically called when an object is instantiated
      // no return type and function name must match class name
      // member initialization list must be in the same order member variables are defined
      // constructors can be overloaded to accept different types of inputs
	  // cannot call constructors from another member function
    Employee() = default;  // default constructor if no arguments are provided

	// delegate constructors call other constructors to reduce duplicate code
	  // often used to map constructors with less arguments to those with more arguments
	  // could alternatively use a single constructor with default value of 0.0 for salary
	Employee(std::string name) 
		: Employee{ name, 0.0 }
	{}
    Employee(std::string name, double salary)
        : m_firstName { name }, m_salary { salary }  // member initialization list (can also be on same line)
    {  
        assert(salary >= 0);
        std::cout << "Employee initialized with name " << name << " and salary $" << salary << '\n';
    }

	// copy constructors are used to initialize an object with an existing object of the same type
	  // not necessarily needed, C++ will use implicit copy constructor if none explicitly defined
	  // can use Employee(const Employee& e) = default to explicitly define the default copy constructor
	Employee(const Employee& e)  // must be a reference
		: m_firstName { e.m_firstName }, m_salary { e.m_salary }
	{}

    // access functions allow you to get or set private class members
    void setName(const std::string& firstName) { m_firstName = firstName; }
    void setSalary(const double& salary) { m_salary = salary; }

    const auto& getName() const { return m_firstName; }  // generally better to return member variables by const reference, avoid non-const reference returns
    double getSalary() const { return m_salary; }  // const implies data members will not be altered
 
    void printEmployee() const
    {
        std::cout << "Name: " << m_firstName << ", Salary: " << m_salary << '\n';
    }
 
    void raise(const double& increase)
    {
        m_salary += increase;
    }
 
    void fires(const Employee& e)
    {
        std::cout << m_firstName << " fires " << e.m_firstName << '\n';
    }
	
};

class Animal 
{
	std::string m_name { "Blank" };
	bool m_pet { false };
	int m_age { 0 };
	int m_id { 0 };
	// static variables can be private as well but can't be accessed without instantiating
	static inline int m_value { 0 }; 
	int* m_dummyArrPtr {};

public:
	// static member variables are the same across all instances of the class
	  // only const integral and enum, and inline types can be defined within the class
	  // useful for things like ID generation and lookup tables that are constant across classes
	static bool mammal;
	static const bool reptile { false };
	static inline int idGen { 0 };  // this is the preferred use of static member variables

	// default constructor
	Animal() = default; 

	// use explicit keyword to prevent implicit argument conversions
	  // can no longer use copy or copy-list initialization 
	  // constructors that take a single argument should typically be explicit
	explicit Animal(const std::string name, bool pet, int age)
		: m_name { name }, m_pet { pet }, m_age { age }, m_id { ++idGen }
	{}

	// static member functions can be called without instantiating an object
	  // static member functions have no "this" pointer
	  // static member functions can only access other static member variables or functions
	static int getValue() { return m_value; }

	// like static member variables, static member functions can be defined outside the class
	static int getID();

	void setArrLength (std::size_t length) { m_dummyArrPtr = new int[length] {}; }

	// "this" is a const pointer that holds the address of the current implicit object
	void getAge() const { std::cout << '\n' << this->m_age << '\n'; }

	void setPet(bool pet)
	{
		this->m_pet = pet; // this->m_pet represents the member function
	}

	// return "this" allows function chaining
	Animal& birthday() { m_age += 1; return *this; }
	Animal& born() { m_age = 0; return *this; }

	// reset class back to default state
	void reset() { *this = {}; }

	// because Animal is a friend of Date, we can access / modify the private members
	void addYear( Date& date )
	{
		date.m_year += 1;
	}

	// a class destructor is automatically called when an object goes out of scope or it is explicitly deleted using the delete keyword
	  // a class can only have a single destructor
	  // The destructor must have the same name as the class, preceded by a tilde (~)
	  // The destructor can not take arguments
	  // The destructor has no return type.
	~Animal()
	{
		delete[] m_dummyArrPtr;
		std::cout << this->m_name << " says goodbye cruel world!\n";
	}
	
};

// static member variables must be defined outside the class in the global scope (unless using inline)
  // you can define static member variables even if they are private or protected
  // if a class is defined in the header, the member variable is usually in the source file
bool Animal::mammal = true;  // now any instantiation of Animal will have mammal = true

// ------- User-Defined Functions -------
void printSalary( const Employee& e ) 
{
	std::cout << "Salary: " << e.getSalary() << '\n';
}

void Date::printDate() const
{
	std::cout << m_month << '/' << m_day << '/' << m_year << '\n';
}

// this non-member friend function can access private and protected members of Date
  // because this is a non-member function, we must explicitly pass the class in to work with
void addMonth(Date& date)
{
	date.m_month += 1;
}

int Animal::getID() { return idGen; }

void classPractice()
{
	std::cout << "\nclassPractice(): \n";

	// calls default constructor
	Employee nobody1;		// default initialization
	Employee nobody2 {};	// value initializaiton (preferred)

	// calls normal constructor
	Employee joe ( "Joe", 13000.0 );	// direct initialization
	Employee sam { "Sam", 14000.0 };	// direct-list initialization (preferred)
	Employee jim = { "Jim", 15000.0 };	// copy-list initialization (non-explicit only)

	// calls delegate constructor
	Employee bob = "Bob"s; 			// copy initialization (non-explicit only)
	bob.setSalary( 12000.0 );
	Employee pam { "Pam" };

	// calls copy constructor 
	Employee bobCopy = bob;			// copy initialization
	Employee joeCopy ( joe );		// direct initialization
	Employee samCopy { sam };		// direct-list initialization (preferred)
	Employee jimCopy = { jim };		// copy-list initialization

	// implicitly convert instantiation to temporary class
	printSalary({"Doug", 1000.0});


	// static member variables and functions can be accessed before any instantiation of the class
	std::cout << "Are all animals mammals? " << Animal::mammal << '\n';
	std::cout << "Value = " << Animal::getValue();
	Animal dog ( "Dog"s, true, 5 );		// direct initialization
	Animal lion { "Lion"s, false, 0 };	// direct-list initialization
	dog.born().birthday().birthday();	// dog is now 2
	dog.getAge();  // C++ is really performing Animal::dog.getName(&dog), where &dog gets assigned to "this"
	std::cout << "Is dog a mammal? " << dog.mammal << '\n';
	std::cout << "Is lion a mammal? " << lion.mammal << '\n';
	dog.setArrLength(10);
	lion.setArrLength(20);


	Date today {};
	addMonth(today);
	today.printDate();

	Date dogBirthday { 6, 17, 2022 };
	dog.addYear(dogBirthday); 


	Cards card { Cards::hearts, 11 };
	std::cout << card.isHearts() << '\n';
}  // class destructors are called here when the class instances go out of scope
