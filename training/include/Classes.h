// ------- Header Guard -------
#ifndef CLASSES_H  
#define CLASSES_H
 
// ------- Forward Declarations -------
void classPractice();


// ------- Class Definition -------
  // class definitions are most often put in a header file so they can be used by other files
  // class header and source files often match the name of the class
  // user-defined types are not subject to the "one definition rule"
  // member functions are implicitly inline
class Date
{
	int m_year { 2026 };
	int m_month { 5 };
	int m_day { 25 };

public: 
	// default constructor
	Date() = default;

	// constructor
	Date(int year, int month, int day)
		: m_year { year }, m_month { month }, m_day { day }
	{}

	// access function definitions are often inside class definition
	int getYear() const { return m_year; }
	int getMonth() const { return m_month; }
    int getDay() const { return m_day; }

	// forward declarations
	  // member functions can be defined outside the class
	  // non-trivial member functions are often defined in source file
	  // best practice to put default values in forward declarations
	void printDate() const;
	void addDay();
};

// use inline keyword to prevent violation of one definition rule for member functions defined outside the class
inline void Date::addDay()
{
	m_day += 1;
} 

class Cards
{
// classes support nested types (member types)
  // nested types must be defined before they can be used, thus ususally at the top of the class
  // can forward declare a type then define elsewhere to reduce clutter
  // nested types do not implicitly get access to member variables and functions of the outer type
public:
	enum Suit
	{
		spades,
		clubs,
		hearts,
		diamonds
	};
	class Dummy;  // forward declaration of nested type

private:
	Suit m_suit {};
	int m_number {};

public:
	// default constructor
	Cards() = default;

	// constructor
	Cards( Suit suit, int num ) : m_suit { suit }, m_number { num } {}

	bool isHearts() { return m_suit == hearts; }  // don't need namespace prefix
	bool isFaceCard() { return m_number > 10; }
};

class Dummy
{

};
 
#endif
