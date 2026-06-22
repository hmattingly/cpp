// ------- Header Guard -------
#ifndef FUNCS_H  // variable typically matches header file name in all caps
#define FUNCS_H  // effectively creating a macro that replaces variable with nothing
 
// ------- Forward Declarations -------
namespace Fr  // forward declarations must be part of the same namespace in which they're defined
{
    // ------- Template Functions -------
    // in leiu of overloaded functions, we can use function templates
      // must be defined in the same file they get instantiated
    template <typename T> // this is the template parameter declaration defining T as a type template parameter (only represents one type)
    T max(T x, T y)
    {
      return (x > y) ? x : y;
    }
 
    template <typename U, typename V>
    auto min(U x, V y)  // allows different types for each parameter and returns an 'auto' type
    {
      return (x > y) ? y : x;
    }
 
}

void functionPractice();

#endif