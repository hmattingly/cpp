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

	double _JD   { 0.0 };	// Julian date referenced from Jan 1, 4713 BC at 12:00 noon UT
	double _JD0  { 0.0 };	// Julian date referenced from Jan 1, 4713 BC at 00:00 midnight UT
	double _MJD  { 0.0 };	// modified Julian date referenced from Nov 17, 1858 at 00:00 midnight UT
	double _T0 	 { 0.0 };	// Julian centuries referenced from Jan 1, 2000 at 00:00 midnight UT
	double _T1 	 { 0.0 };	// julian centuries referenced from Jan 1, 2000 at 12:00 noon UT

public:
	// default constructor (disabled)
	Epoch() = default;

	// parameterized constructor
	Epoch(const int& year, const int& month, const int& day, const double& utc);

	// destructor
	~Epoch() = default;

	// forward declarations

	// access functions
	const int& getYear() const { return _year; }
	const int& getMonth() const { return _month; }
	const int& getDay() const { return _day; }
	const double& getUTC() const { return _utc; }
	const double& getJD() const { return _JD; }
	const double& getJD0() const { return _JD0; }
	const double& getMJD() const { return _MJD; }
	const double& getT0() const { return _T0; }
	const double& getT1() const { return _T1; }

	// setter functions
	void update(const double& dt);

};

#endif  // EPOCH_HH
