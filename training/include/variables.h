// Header files allow us to put declarations in one place and then import them wherever we need them
  // typically avoid large function definitions in header files (or use inline keyword)
  // iostream is an example of a standard library header file
  // implicitly included by #include directives and compiled as part of source files
 
// Header files consist of 1) a header guard and 2) content of the header file (declarations)
  // header guards prevent from *defining* an object more than once (compiler error)
  // more than one declaration of the same object is perfectly fine
 
// ------- Header Guard -------
#ifndef VARIABLES_H  
#define VARIABLES_H  
 
// ------- Forward Declarations -------
// another option is to define global constants in header files (this is typically preferred)
  // cannot forward declare constant expressions
  // const globals have internal linkage by default so they don't violate the "one definition rule" 
const int CONSTANT1 { 200 };    		// each source file that includes this header gets a copy of CONSTANT1
inline int CONSTANT2 { 300 }; 			// use keyword inline to prevent violation of the "one definition rule" since CONSTANT2 has external linkage by default  
inline const int CONSTANT3 { 400 };		// each source file that includes this header shares a single instance of CONSTANT3	

int variablePractice();
void dataTypes();

#endif