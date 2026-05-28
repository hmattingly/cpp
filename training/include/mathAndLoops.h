// Header files allow us to put declarations in one place and then import them wherever we need them
  // typically avoid function definitions in header files
  // iostream is an example of a standard library header file
  // implicitly included by #include directives and compiled as part of source files
 
// Header files consist of 1) a header guard and 2) content of the header file (declarations)
  // header guards prevent from *defining* an object more than once (compiler error)
  // more than one declaration of the same object is perfectly fine
 
// ------- Header Guard -------
#ifndef MATLOOP_H  
#define MATLOOP_H  
 
// ------- Forward Declarations -------
// another option is to define global constants in header files
  // cannot forward declare constant expressions
  // const globals have internal linkage by default so they don't violate the "one definition rule" 
    // each source file that includes this header gets a copy of CONSTANT1
  // use keyword inline to prevent violation of the "one definition rule"
    // each source file that includes this header shares a single instance of CONSTANT2
const int CONSTANT1 { 200 };          
inline const int CONSTANT2 { 300 };
inline int CONSTANT3 { 400 }; 
 
// forward declare a constant if it's defined in another source file by using extern
  // extern declares a variable or function without allocating memory for it
extern const double g_gravity;
 
void mathPractice(int x=2, int y=3);  // put default values in forward declarations
bool conditionalPractice();
void loopPractice();
 
#endif
