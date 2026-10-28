/*
** ------------ Header Guard -------------
*/ 
#ifndef EPOCH_HH  
#define EPOCH_HH

/*
** ------- Preprocessor directives -------
*/ 

/*
** -------------- Constants ---------------
*/ 

/*
** -------- Forward Declarations ----------
*/ 

/*
** --------- Namespace directives ---------
*/ 

/*
** ----------- Class Definition ------------
*/ 
class Epoch
{
private:
	int _year 	{ 2000 };	// year (4 digit format)
	int _month 	{ 1 };		// month (month number 1-12)
	int _day 	{ 1 };		// day of month
	double _utc { 0.0 };	// UTC provided in hours

public:
	// default constructor (disabled)
	Epoch() = default;

	// parameterized constructor
	Epoch(const int& year, const int& month, const int& day, const double& utc);

	// destructor
	~Epoch() = default;

	// forward declarations
	double getJD();
	double getJD0();
	double getMJD();
	double getT0();
	double getT1();
	double getGMST();

	// access functions
	int getYear() const { return _year; }
	int getMonth() const { return _month; }
	int getDay() const { return _day; }
	double getUTC() const { return _utc; }

	// setter functions
	void update(const double& dt);

};

#endif  // EPOCH_HH
