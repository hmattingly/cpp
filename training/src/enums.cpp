// ------- Preprocessor directives -------
#include "enums.h"
#include <iostream>
 
// we can use the following compound data types to create user-defined types
  // Enumerations (scoped and unscoped)
  // Classes (structs, classes, and unions)
 
// Define user-defined types in the global scope so they can be used anywhere within this file (optional)
  // more common to put the user-defined type in its own header file
 
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
