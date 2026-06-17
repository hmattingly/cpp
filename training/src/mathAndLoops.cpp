// ------- Preprocessor directives -------
#define NDEBUG             // disables assert() functions (must be placed before #includes)
#include "mathAndLoops.h"  // best practice to include corresponding header (helps with catching errors)
#include <iostream>        // iostream is part of the standard C++ library that deals with basic input and output
#include <cmath>           // for math functions
#include <cassert>         // for assert
 
#define PI 3.14159265358979323846  // object-like macros allow substitution of values, functionally equivalent to constants but prefer constants
 
// ------- Namespace directives -------
namespace // unnamed (ananonymous) namespace forces internal linkage (same as static)
{
    int doo { 1 };
}
 
// ------- Global variables -------
  // const and constexpr have internal linkage by default (can only be accessed in this source file)
  // non-const variables and functions have external linkage by default (can be accessed in any source file)
const double g_gravity { 9.81 };     // const objects cannot be re-assigned. Must be initialized when defined. g_ prefix sometimes used for globals
constexpr int expression { 3 + 5 };  // constant expressions must be known at compile time, allows the compiler to simplify code
static int s_foo { 1 };              // static keyword forces internal linkage, s_ prefix sometimes used for static
 
// ------- User-Defined Functions -------
void mathPractice(int x, int y)  
{
 
    assert(x == 2);     // use assert() to check constraints on function parameters
    assert(y == 3);
    double z { PI*x };  // use PI macro here
    s_foo = x + y;      // can alter s_foo here because its global non-const
    doo = x - y;        // can alter doo here because its global non-const
 
    x += y;  // x = x + y
    x -= y;  // x = x - y
    x *= y;  // x = x * y
    x /= y;  // x = x / y
    x %= y;  // x = x % y
    x++;     // copy x, then increment, then return the copy
    x--;     // copy x, then decrement, then return the copy
    ++x;     // increment x, then return x. Typically preferred / less likely to cause issues
    --x;     // decrement x, then return x. Typically preferred / less likely to cause issues
 
    int a { y++ };  // a=y=3, y=y+1=4
    int b { ++y };  // y=y+1=5, b=y=5
   
    double c { std::pow(a, b) };  // c = a^b
 
}
 
bool conditionalPractice()
{
    std::cout << "\nconditionalPractice(): \n";
   
    int x {};
    int y { 4 };
    int z { ( x == 0 ) ? x : y }; // ternary operator: c?a:b -> If c is true, evaluate/return a, otherwise evaluate/return b
 
   
    // use switch instead of multiple if statements that test for equality. Does not support non-integral types (e.g. strings or floats)
    switch ( z )  // can be a conditional statement but that sort of defeats the purpose (use if instead)
    {  // conventional not to indent case labels
   
    case 0:                 // case labels must be constant expressions
        x = 1;              // you can define variables anywhere
        std::cout << "z is 0\n";
        break;              // without break, the subsequent statements will also be executed after the first matching case
    case 4:
        std::cout << "z is 4\n";
        [[fallthrough]];    // optional but tells the compiler that fallthrough is intentional
    default:                // default works like an else statement and is optional
        double a { g_gravity*2.0 };  // you can only initialize variables in the last case
        std::cout << "z is neither 0 nor 4\n";
        break;
    }
 
tryAgain:  // statement label, conventional not to indent (same as case labels)
    if ( y <= 6 )
    {
        y++;
        goto tryAgain;  // goto and statement label must be in the same function, avoid!
    }
       
 
    // logical operators:
        // AND: && or and
        // OR: || or or
        // NOT: ! or not
        // fun note: !(x && y) = !x || !y;   !(x || y) = !x && !y;
 
    if (x == 0)
        std::cout << "I can execute single statements without brackets!\n";
    else if (y)         // y is converted to boolean, any non-zero and non-empty value is true
    {                   // use brackets for more than one statement
        int voo { 2 };  // variables defined in an if statement are local to that block
        return false;   // early return
    }
    else
        std::cout << "idk something\n";
   
    return true;
 
}
 
void loopPractice()
{
    int x { 0 };
    // while loop
    while ( x < 5 )
    {
        ++x;
    }
 
    // do while loop. The following are equivalent:
    x = 5;
    while ( true )
    {
        if ( x == 0 )
            break;
        --x;
    }
 
    x = 5;
    do // favored over above
    {
        --x;
    } while ( x > 0 );


    // for loop: for (initialization; condition; end-expression) { ... }
    for ( int k { 0 }; k < 5; ++k )  // will continue to evaluate until the condition is false (e.g. when x = 5)
    {
        int y { k };  // if a variable is only used inside the loop, better to initialize within the loop
        if ( y == 2 )
            continue;
        ++y;
    }
 
    for ( ; x < 5; )  // can omit initialization, condition, and/or end-expression if desired
    {
        ++x;
    }
 
}
