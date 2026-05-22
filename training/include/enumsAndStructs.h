// ------- Header Guard -------
#ifndef ENUMSTRUCTS_H  
#define ENUMSTRUCTS_H  
 
// ------- Forward Declarations -------
void enumPractice();
void structPractice();
 
// ------- Template Classes -------
template <typename T>
struct CartCoords  // allows different types for structure memebers
{
    T x {};
    T y {};
    T z {};
};
 
template <typename U, typename V>
struct CylinCoords
{
    U radius {};
    V theta {};
    V phi {};
};


#endif
