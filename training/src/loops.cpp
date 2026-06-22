// ------- Preprocessor directives -------
#include "loops.h"  	// best practice to include corresponding header (helps with catching errors)
#include <iostream>     // iostream is part of the standard C++ library that deals with basic input and output
 
// ------- User-Defined Functions -------
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