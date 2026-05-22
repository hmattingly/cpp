// ------- Preprocessor directives -------
#include "enumsAndStructs.h"
#include "Fraction.h"
#include <iostream>
#include <string_view>
 
// we can use the following compound data types to create user-defined types
  // Enumerations (scoped and unscoped)
  // Classes (structs, classes, and unions)
 
// Define user-defined types in the global scope so they can be used anywhere within this file (optional)
  // more common to put the user-defined type in its own header file (e.g. Fraction.h)
 
// ------ Unscoped Enumerations -------
  // enumerations are best for a small set of related constants, and objects only need to hold one of the values at a time
enum Color
{
    // The following are enumerators, which are symbolic constants separated by a comma
      // enumerators define all the possible values the data type can hold
      // the symbolic constants have values that are of integral type. Values are assigned in the order they are defined
      // booleans are essentially enumerations with true and false enumerators
    red,    // 0, typically want the default enumerator to be 0. If no good default exists, use something like invalid or unknown
    green,  // 1
    blue    // 2
};  // user-defined types definitions must end in a semicolon
 
// cannot use the same enumerator in different enumerations in the same scope. One solution: use namespaces
namespace Suit
{
    enum Suit : std::int16_t // specify a base type instead of using the default (optional)
    {
        spades = -3,    // you can manually assign the enumerator value
        clubs,          // next undefined enumator value will be +1 the previous. -3 + 1 = -2
        diamonds = 5,   // enumerators can share the same value, though should be avoided
        hearts = 5
    };
}
namespace Body
{
    enum Body
    {
        arms,
        legs,
        heads,
        hearts
    };
}
 
// ------ Scoped Enumerations -------
  // no implicit conversion from enumerator to integral
  // act like a namespace for their enumerators
  // typically favored over unscoped for the above reasons unless there is a reason to convert to integral without static_cast
enum class Color2
{
    yellow,
    orange,
    purple
};
 
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
 
void enumPractice()
{
    // unscoped enumerations
    Color apple { red };
    Color sky { blue };
    Color defaultColor {};  // will initialize to red
    Color fire { static_cast<Color>(0) };  // converts value 0 to its corresponding enumerator
 
    Suit::Suit card { Suit::hearts };
    Body::Body me { Body::hearts };
 
    // the == and != operators can be used with enumerations
    if (apple == red)
        ;  // do nothing
 
    std::cout << "\nBody::hearts = " << me << '\n';  // compiler can implicitly convert enumerator to integral
   
 
    // scoped enumerations
    Color2 grape { Color2::purple };
    Color2 lemon { static_cast<Color2>(0) };  // converts value 0 to its corresponding enumerator
   
    if (grape == Color2::purple)
        ;  // do nothing
 
}
 
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
 
}
