// ------- Preprocessor directives -------
#include "classes.h"    // best practice to include corresponding header (helps with catching errors)
#include <iostream>     // because we need std::cout, must include iostream here
#include <string_view>
#include <cassert>      // for assert
 
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
    std::string_view m_name { "Blank" };
    double m_salary { 0.0 };
 
public:  // access specifier
   
    // constructors are special member functions that are automatically called when an object is instantiated
      // no return type and function name must match class name
      // member initialization list must be in the same order member variables are defined
      // constructors can be overloaded to accept different types of inputs
    Employee() = default;  // default constructor if no arguments are provided
    Employee(std::string_view name, double salary)
        : m_name { name }, m_salary { salary }  // member initialization list (can also be on same line)
    {  // usually function body is left empty
        assert(salary >= 0);
        std::cout << "Employee initialized with name " << name << " and salary $" << salary << '\n';
    }
 
    // access functions allow you to get or set private class members
    void setName(const std::string_view& name) { m_name = name; }
    void setSalary(const double& salary) { m_salary = salary; }
    const auto& getName() { return m_name; }  // generally better to return member variables by const reference, avoid non-const reference returns
    double getSalary() const { return m_salary; }  // const implies data members will not be altered
 
    void printEmployee() const
    {
        std::cout << "Name: " << m_name << ", Salary: " << m_salary << '\n';
    }
 
    void raise(const double& increase)
    {
        m_salary += increase;
    }
 
    void fires(const Employee& e)
    {
        std::cout << m_name << " fires " << e.m_name << '\n';
    }
 
};
 
// ------- User-Defined Functions -------
void classPractice()
{
    Employee bob { "Bob",12000.0 };
    bob.raise(1000.0);
    bob.printEmployee();
   
    Employee newGuy {};
    newGuy.setName("Sam");
    bob.fires(newGuy);
}
