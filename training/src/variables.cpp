// ------- Preprocessor directives -------
#include <iostream>    // iostream is part of the standard C++ library that deals with basic input and output
#include <cstdint>     // for fixed-width integers
#include <string>      // for string
#include <string_view> // for string_view
 
// ------- Namespace directives -------
// using creates an alias for an existing name or data type
using std::string;        // brings std::string into global scope. Now can use string without std:: prefix
using std::string_view;  
using namespace std::literals::string_literals;
using namespace std::literals::string_view_literals;
// std is the standard namespace. Bringing in the entire std namespace is discouraged
  // :: is the scope resolution operator
 
// ------- User-Defined Functions -------
  // Function format:
  // [return data type] [function name]([input 1 type and name], ..., [input n type and name]) {[function definition]}
int variablePractice()
{
   
    // 6 types of initialization
    int a;            // default initialization (no initializer), variable assigned garbage value.. typically avoid
    int b = 2;        // copy-initialization (traditional)
    int c ( 2 );      // direct-initialization (traditional)
    int d { 2 };      // direct-list-initialization (modern and preferred), prevents narrowing conversion
    int e = { 2 };    // copy-list-initialization (uncommon)
    int f {};         // value-initialization (modern and preferred), initializes to 0 or default value
 
    // define multiple variables on the same line
    // variables of different types must be on separate lines
    int g, h;
    int i { 2 }, j { 3 };
 
    // static local variables do not go out of scope after the function ends. They are initialized only once, the first time the function is called
    static int m { 3 };  // if this function were called again, this line would be skipped since m is already initialized
    m++;
 
    [[maybe_unused]] int n { 3 };  // to prevent unused variable warning use [[maybe_unused]]
 
    return m;  // return integer
}
 
// functions with no return value have type void 
void dataTypes()  
{  
 
    // Integers (signed by default)
    short a { 1 };               // typically 2 bytes
    int b { 2 };                 // typically 4 bytes
    long c { 3 };                // typically 4 bytes
    long long d { 4 };           // typically 8 bytes
 
    std::int8_t e { 5 };         // forces a signed 8 bit (1 byte) integral type (typically resolves to char)
    std::int16_t f { 6 };        // forces a signed 16 bit (2 byte) integral type
    std::int32_t g { 7 };        // forces a signed 32 bit (4 byte) integral type
    std::int64_t h { 8 };        // forces a signed 64 bit (8 byte) integral type
 
    std::int_fast16_t i { 9 };   // assigns fastest signed integral type that's at least 16 bits. Fastest = processed most quickly. Not recommended
    std::int_least16_t j { 10 }; // assigns smallest signed integral type with a width of at least 16 bits. Not recommended
 
      // integer literals are type signed int by default
    long k { 11l };              // converts the literal 11 to long
    long long l { 12ll };        // converts the literal 12 to long long
 
      // adding "int" to the end of short, long, and long long is not necessary. The following are equivalent:
    short m;
    signed short n;
    signed short int o;
    short int p;
 
    // Unsigned Integers
      // use the "unsigned" keyword to make an integer unsigned (generally discourged due to possible overflow)
      // when comparing unsigned numbers to signed, the result is always unsigned
    unsigned short q { 1 };
    unsigned int r = -1;         // overflow -> undefined behavior
    std::int16_t s { 2 };        // forces an unsigned 16 bit (2 byte) integral type
 
    std::int_fast16_t t { 3 };   // assigns fastest unsigned integral type that's at least 16 bits. Fastest = processed most quickly. Not recommended
    std::int_least16_t u { 4 };  // assigns smallest unsigned integral type with a width of at least 16 bits. Not recommended
 
    unsigned long v { 5ul };     // converts the literal 5 to unsigned long
    unsigned long long w { 6ull };// converts the literal 6 to unsigned long long
 
    // Floating Points
    float x { 1.0 };             // typically 4 bytes, best practice to include decimal when defining floating point literals
    double y { 1.1 };            // typically 8 bytes
    long double z { 1.2 };       // typically 16 bytes
 
      // decimal literals are type double by default
    float aa { 1.3f };           // converts the literal 1.3 to float
    long double bb { 1.4l };     // converts the literal 1.4 to to long double
 
    // Booleans
    bool cc { true };
    bool dd {};                  // defaults to false
    bool ee { 1 };               // true when 1, false when 0  (direct-list-initialization)
    bool ff = 4;               // true when any value != 0, false when 0  (copy-initialization)
 
    std::cout << std::boolalpha; // prints booleans as true or false instead of 1 or 0
    std::cout << "\nTrue = " << ff << '\n';
 
    // Characters and Strings
    char gg { '2' };             // characters use single quotes
    string hh { "two" };         // strings / text use double quotes
 
      // single quote characters are type char by default
      // double quote strings are type C-style string by default
    string ii { "three"s };      // converts the literal "three" to string
    string_view jj { "four"sv }; // converts the literal "four" to string_view
 
   
    // use static_cast to explitly convert one type to another. static_cast<new type>(expression)
    int kk { static_cast<int>(a) };
    float ll { static_cast<float>( 2 / 3) };
 
    // c++ supports a variety of literals
      // use std::dec, std::hex to force decimal or hex output
    double mm { 2.1e2 };          // scientific notation for large numbers, must use floating types
    int nn { 0b1111 };            // binary literal (15)
    int oo { 0xF };               // hexadecimal (15). 2 hex digits = 1 byte
    int pp { 123'456'789 };       // single quotes allow for better readability
 
    // can use auto when initializing to let compiler deduce type. auto will drop const
    auto qq { 123 };              // int
    auto rr { 1.2 };              // double
    auto ss { 1.2f };             // float
 
    // Constants
    const double tt { 9.81 };     // const objects cannot be re-assigned. Must be initialized when defined
    constexpr int uu { 3 + 5 };   // constant expressions must be known at compile time, allows the compiler to simplify code
 
    // the following operators require operands of the same type:
      // +, -, *, /, %
      // <, >, <=, >=, ==, !=
      // &, |, ?
 
    // (float / double) (operator) (integral) = (float / double)
    // promotions follow the following ranking:
      // long double
      // double
      // float
      // long long
      // long
      // int
 
   
    std::cout << "A byte is    " << CHAR_BIT << " bits\n";
    std::cout << "bool:        " << sizeof(bool) << " bytes\n";
    std::cout << "char:        " << sizeof(char) << " bytes\n";
    std::cout << "short:       " << sizeof(short) << " bytes\n";
    std::cout << "int:         " << sizeof(int) << " bytes\n";
    std::cout << "long:        " << sizeof(long) << " bytes\n";
    std::cout << "long long:   " << sizeof(long long) << " bytes\n";
    std::cout << "float:       " << sizeof(float) << " bytes\n";
    std::cout << "double:      " << sizeof(double) << " bytes\n";
    std::cout << "long double: " << sizeof(long double) << " bytes\n";
}
