// ------- Header Guard -------
#ifndef MATH_H  
#define MATH_H  

// ------- Forward Declarations -------

// forward declare a constant if it's defined in another source file by using extern
extern const int g_mathConst1;  // explicitly convert g_mathConst1 from internal to external linkage
extern int g_mathConst2;        // extern keyword still required even though g_mathConst2 has external linkage by default

void mathPractice(int x=2, int y=3);  // put default values in forward declarations

#endif
