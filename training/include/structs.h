// ------- Header Guard -------
#ifndef STRUCTS_H  
#define STRUCTS_H  
 
// ------- Forward Declarations -------
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

// ------- Structure Definition -------
struct Fraction {  // convention is to start with a capital letter
    int numerator {};
    int denominator { 1 };

	double getPercent() const
	{
		return ((static_cast<double>(numerator) / static_cast<double>(denominator)) * 100.0);
	}

};  // user-defined types definitions must end in a semicolon


#endif
