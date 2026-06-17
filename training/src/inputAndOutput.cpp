// ------- Preprocessor directives -------
#include <iostream>    // iostream is part of the standard C++ library that deals with basic input and output
#include <string>      // for string
 
// ------- User-Defined Functions -------
int variablePractice();

void outputPractice()
{

    std::cout << "\noutputPractice(): \n";
   
    int m { variablePractice() };  // returns m = 4
 
    // common predefined variables in iostream
      // cout = character output
      // endl = end line, equivalent to \n but flushes the buffer (not preferred)
      // cin  = character input
      // cerr = character error, equivalent to cout but flushes the buffer, used for debugging
 
    std::cout << "Hello world!\n";         // insertion operator << and extraction operator >> move data in direction pointed
   
    // Quoted text separated by nothing but whitespace (spaces, tabs, or newlines) will be concatenated
    std::cout << "Hi "
                 "World\n";
 
    // Statements can be split over multiple lines
    std::cout
      << "Hola World\n";
 
    std::cerr << "I'm helping to debug!\n";
 
    std::cout << "1st call: m = " << m << std::endl;
    std::cout << "1st call: m = " << m << '\n';      // conventional to put \n in single quotes
    std::cout << "2nd call: m = " << variablePractice() << '\n';  // returns m = 5
 
}
 
void inputPractice()
{
    std::cout << "\ninputPractice(): \n";

    // Notes on extraction opertor:
      // removes all leading whitespace characters
      // extracts as many characters as it can until it hits \n (Enter) or invalid entry per data type of variable extracted to (e.g. whitespace)
      // returns 0 if invalid entry per data type of variable being extracted to and discontinues further extraction
   
    int x {}, y {};
    std::cout << "Enter two integers separated by space or new line: ";
    std::cin >> x >> y;                    // automatically adds new line
    std::cout << "You entered: " << x << " and " << y << '\n';
   
    std::string s {};
    std::cout << "Enter a word: ";
    std::cin >> s;
    std::cout << "Your word has " << s.length() << " characters.\n";
}
