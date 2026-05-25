// ------- Preprocessor directives -------
#include "structs.h"
#include <iostream>
#include <string_view>
 
// we can use the following compound data types to create user-defined types
  // Enumerations (scoped and unscoped)
  // Classes (structs, classes, and unions)
 
// Define user-defined types in the global scope so they can be used anywhere within this file (optional)
  // more common to put the user-defined type in its own header file 
 
// ------ Structures -------
struct Employee
{
// Three types of access exist: public, private, and protected
  // struct members are public by default meaning they can be accessed by members and non-members
  // best practice is all members should always be public
 
    // member functions and variables can be defined in any order
    // the following are data members (or member variables or properties)
    std::string_view name {};
    int id {};
    int age {};
    double salary {};
    bool remote { false };  // default value is false
 
    // the following are member functions (methods)
      // member functions must be declared
      // member functions can be overloaded
      // best practice to avoid defining constructor member functions
      // const member functions do not alter any member variables or call any non-const member functions
        // can still modify non-member variables, and call non-member functions
    void printEmployeeFromStruct() const // do not need to pass in member variables
    {
        std::cout << "Name: " << name << ", ID: " << id << ", Age: " << age << ", Salary: " << salary << ", Remote: " << remote << '\n';
    }
 
    void raise(const double increase)
    {
        salary += increase;
    }
 
};
 
void printEmployee(const Employee& e)  // structures are typically passed by reference
{
    std::cout << "Name: " << e.name << ", ID: " << e.id << ", Age: " << e.age << ", Salary: " << e.salary << ", Remote: " << e.remote << '\n';
}
 
void structPractice()
{
    Employee bob {};
    bob.name = "Bob";
    bob.id = 5;
    bob.age = 30;
    bob.salary = 10000.0;
    bob.remote = false;
 
    // aggregate initialization follows the order in which struct data members are defined
    Employee joe { "Joe", 6, 33, 20000.0 };              // remote defaulted to false
    const Employee sam { "Sam", 7, 34, 30000.0, true };  // sam never getting a raise since const
    // const objects cannot call non-const member functions. E.g. sam.raise(100); will not work
 
    joe = { joe.name, joe.id, 34, joe.salary };  // joe had a birthday
   
    printEmployee(bob);
    printEmployee({ "Dummy", 8, 35, 11000.0 });
    bob.printEmployeeFromStruct();
    bob.raise(1000.0);
    std::cout << "Bob's new salary is: " << bob.salary << '\n';
 
    Employee* bobPtr { &bob };            // pointer to structure
    double bobSalary { bobPtr->salary };  // use the -> operator to access the data member from a structure pointer. Equivalent to (*bobPtr).salary
 
    CartCoords<int> point1 { 10, 20, 30 };
    CartCoords<double> point2 { 10.2, 20.3, 30.7 };
    CylinCoords<int, double> point3 { 10, 20.3, 30.7 };  // CylinCoords template uses two different template parameters
    using Point = CylinCoords<int, double>;  // use aliases to make code more readable
    Point point4 { 10, 20.3, 30.7 };

	// pull in class from header
	Fraction x { 1, 4 };
	std::cout << x.numerator << " divided by " << x.denominator << " gives " << x.getPercent() << "%\n";

}
