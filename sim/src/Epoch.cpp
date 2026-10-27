/*
** ------- Preprocessor directives -------
*/ 
#include "Epoch.hh"
#include "Constants.hh"
#include <cmath>

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
Epoch::Epoch(const int& year, const int& month, const int& day, const double& utc) :
	_year { year }, _month { month }, _day { day }, _utc { utc }
{
	
}

double Epoch::getJD0()
{
	return std::floor( 365.25 * _year ) + std::floor( 30.6001 * ( _month + 1 ) ) - 15.0 + 1720996.5 + _day;
}

double Epoch::getJD()
{
	return getJD0() + _utc / 24.0;
}

double Epoch::getMJD()
{
	return getJD() - 2400000.5;
}

double Epoch::getT0()
{
	return ( getJD0() - 2451545.0 ) / 36525.0;
}

double Epoch::getT1()
{
	return ( getJD() - 2451545.0 ) / 36525.0;
}

double Epoch::getGMST()
{
	double T0 { getT0() };
	double T1 { getT1() };
	double utcSec { _utc * 3600.0 };
	double gmstDeg { 24110.54841 + 8640184.812866 * T0 + 0.093104 * T1 * T1 - 0.0000062 * T1 * T1 * T1 + 1.00272790935 * utcSec };
	gmstDeg = std::fmod( gmstDeg / 240.0, 360.0 );
	if ( gmstDeg < 0.0 )
	{
		gmstDeg += 360.0;
	}
	
	return gmstDeg * DEG2RAD;
}
