// ------- Preprocessor directives -------
#define NDEBUG             // disables assert() functions (must be placed before #includes)
#include "math.h"          // best practice to include corresponding header (helps with catching errors)
#include <iostream>        // iostream is part of the standard C++ library that deals with basic input and output
#include <cmath>           // for math functions
#include <cassert>         // for assert
 
// ------- Global variables -------
const int g_mathConst1 { 100 };     // internal linkage by default
int g_mathConst2 { 200 };           // external linkage by default

// ------- User-Defined Functions -------
void mathPractice(int x, int y)  
{
 
    assert(x == 2);     // use assert() to check constraints on function parameters
    assert(y == 3);
 
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

 

