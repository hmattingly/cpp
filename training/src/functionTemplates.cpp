// ------- Preprocessor directives -------
#include "functionTemplates.h"    // best practice to include corresponding header (helps with catching errors)
#include <iostream>          // because we need std::cout, must include iostream here
#include <string>
 
// ------- User-Defined Functions -------
  // namespaces must be defined at the global level
namespace Fr  // typical convention is capitalized first letter
{  
 
    // overloaded functions can have the same name but different parameters
    int add(int x=5, int y=10) {  // if we call add(1, 2) this function will be called
        // 5 and 10 are default parameters
        // default parameters can be included in either the function forward declaration OR the function definition
          // more common to include them in the forward declaration
        // all input parameters to the right of a default must also have defaults. e.g int x=5, int y is not allowed
        return x + y;
    }
 
    double add(double x, double y=10.0) {  // if we call add(1.0, 2.0) or add(1, 2.0) this function will be called
        return x + y;
    }
 
}
