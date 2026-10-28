/*
** ------- Preprocessor directives -------
*/ 
#include "Epoch.hh"
#include "Constants.hh"
#include <cmath>	// for std::fmod()
#include <cassert>	// for assert()

/*
** -------------- Constants ---------------
*/ 

/*
** -------- Forward Declarations ----------
*/ 

/*
** --------- Namespace directives ---------
*/ 
using namespace Constants;

/*
** ----------- Class Definition ------------
*/ 
Epoch::Epoch(const int& year, const int& month, const int& day, const double& utc) :
	_year { year }, _month { month }, _day { day }, _utc { utc }
{
	// JD conversions are only valid for these dates
	assert( _year >= 1901 & _year <= 2099 );
}

double Epoch::getJD0()
{
	// julian date referenced from Jan 1, 4713 BC at 00:00 midnight UT
	return ( 1'721'013.5 + 367 * _year + std::floor( ( 7.0 / 4.0 ) 
			 * std::floor( ( _month + 9.0 ) / 12.0 ) ) 
			 + std::floor( 275.0 * _month / 9.0 ) + _day );
}

double Epoch::getJD()
{
	// julian date referenced from Jan 1, 4713 BC at 12:00 noon UT
	return getJD0() + _utc / 24.0;
}

double Epoch::getMJD()
{
	// modified Julian date referenced from Nov 17, 1858 at 00:00 midnight UT
	return getJD() - 2'400'000.5;
}

double Epoch::getT0()
{
	// julian centuries referenced from Jan 1, 2000 at 00:00 midnight UT
	return ( getJD0() - 2'451'545.0 ) / 36'525.0;
}

double Epoch::getT1()
{
	// julian centuries referenced from Jan 1, 2000 at 12:00 noon UT
	return ( getJD() - 2'451'545.0 ) / 36'525.0;
}

double Epoch::getGMST()
{
	// greenwich mean sidereal time
	double T0 { getT0() };
	double utcSec { _utc * 3600.0 };
	double gmstSec { 24'110.54841 + 8'640'184.812866 * T0 
					 + 0.093104 * T0 * T0
					 - 0.0000062 * T0 * T0 * T0
					 + 1.002737909350795 * utcSec };

	// convert from sec to rad
	double gmst = std::fmod( gmstSec / 240.0, 360.0 ) * DEG2RAD;
	if ( gmst < 0.0 )
	{
		gmst += TWO_PI;
	}
	
	return gmst;
}

void Epoch::update(const double& dt)
{
	_utc += dt / 3600.0;
	if ( _utc > 24.0 )
	{
		_utc -= 24.0;
		_day += 1;
	}
}
