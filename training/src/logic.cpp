// ------- Preprocessor directives -------
#include "logic.h"  // best practice to include corresponding header (helps with catching errors)
#include <iostream>        // iostream is part of the standard C++ library that deals with basic input and output

 
// ------- User-Defined Functions -------

bool logicPractice()
{
    std::cout << "\nlogicPractice(): \n";
   
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
        double a { 2.0 };  // you can only initialize variables in the last case
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
 