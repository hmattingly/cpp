// ------- Preprocessor directives -------
  // always start with # and don't have semicolons
 
  // #include usually used to bring in header files (.h), discouraged to bring in source files
  // <> brings in std library headers while "" brings in project headers
  // #include is literally replacing the directive with the contents of the file
  // it is best practice to always explicitly #include all header files needed for the source to compile
  // best practice sequence: paired header file, project header(s), 3rd party header(s), standard library header(s)
#include "functionTemplates.h"
#include "refsAndPointers.h"
#include "mathAndLoops.h"
#include "enums.h"
#include "structs.h"
#include "classes.h"
#include "containers.h"
//#include <cstdlib>   // for exit and abort
 
  // #define is used to define macros.
// #define VARIO        // replaces VARIO with nothing
// #define MATLOOP
// #define FUNCSREFS
// #define ENUMSTRUCTS
// #define CLASSES
// #define CONTAINERS
 
// ------- Namespace directives -------
  // using creates an alias for an existing name or data type
using namespace Fr; // brings in the entire Fr namespace to global scope
 
// ------- User-Defined Functions -------
  // user defined functions go before main(), i.e. functions must be declared before they are called
  // function forward declaration / function prototype allows function to be called before it is defined
void forwardDeclaration(int voo, int doo);
 
  // must tell the compiler about the existence of a function defined in another file
  // function must be defined and externally linked
  // forward declarations must be part of the same namespace
void inputPractice();
void outputPractice();
void dataTypes();
 
// ------- MAIN -------
  // function main() will always be called first regardless of where it is located
  // all C++ programs require a function named main
  // explicit function calls to main are not allowed
  // main is required to return an integer
int main()  // returns integer, typical for main to indicate successful execution
{
    // must terminate all statements with semicolons  
 
    /*
    This is how you add add a multi-line comment
    */
 
    // Quickly comment out lines with Ctrl + /
   
    // can use std::atexit(cleanup) where cleanup is some function pointer that will run when you execute std::exit(). The function cannot take parameters
    // can use std::exit(0) to exit the program cleanly, where 0 is the exit code. Functionally the same as ending main()
    // can use std::abort() or std::terminate() to immediately exit the program. By default, std::terminate() calls std::abort()
 
    // nested functions are not supported in C++
 
    #ifndef TEST  // preprocessor directive that compiles if TEST is not defined
    forwardDeclaration(2,3);
    #endif
 
    #ifdef VARIO  // preprocessor directive that compiles if VARIO is defined
    dataTypes();
	inputPractice();
    outputPractice();
    #endif
 
    #ifdef MATLOOP
    mathPractice();
    conditionalPractice();
    loopPractice();
    #endif
 
    #ifdef FUNCSREFS
    referencePractice();
    pointerPractice();
    // instantiate template functions (implicitly inline)
    int a { Fr::max<int>(2,3) };  // populates template parameter with int
    auto b { Fr::max(2,3) };      // alternatively let the compiler deduce the template parameter from the input arguments
    auto c { Fr::min(2.0,3) };    // min returns auto type
    #endif
 
    #ifdef ENUMSTRUCTS
    enumPractice();
    structPractice();
    #endif
 
    #ifdef CLASSES
    classPractice();
    #endif

	#ifdef CONTAINERS
	vectorPractice();
	arrayPractice();
	multiDimPractice();
	#endif
   
    return 0;
}  // all local variables are destroyed at the end of their function
// classes must be destructed prior to destruction
 
void forwardDeclaration(int, int)  // in this case the parameters are not used (avoids compiler warning)
{
    // do nothing
}
