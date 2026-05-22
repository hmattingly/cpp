// ------- Preprocessor directives -------
#include "Scheduler.h"  
#include <iostream>     // because we need std::cout, must include iostream here
#include <string_view>
#include <cassert>      // for assert
 
// Class member definitions
Scheduler::Scheduler()
{
    if (!m_exists) {
        m_exists = true;
    }
    else {
        std::cout << "Error: Scheduler already exists\n";
    }
 
    m_seconds = 0;
}
 
const int& Scheduler::getSeconds() { return m_seconds; }
const double Scheduler::getMinutes() { return static_cast<double>(m_seconds) / 60.0; }
void Scheduler::incrementSeconds() { m_seconds++; }
