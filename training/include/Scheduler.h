// ------- Header Guard -------
#ifndef SCHEDULER_H  
#define SCHEDULER_H
 
// ------- Forward Declarations -------
class Scheduler
{
    static bool m_exists;  // static member variables will be the same across all instances of an object
    int m_seconds;
 
public:
    Scheduler() = default;
    const int& getSeconds();
    const double getMinutes();
    void incrementSeconds();
 
};
 
#endif
