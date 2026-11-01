/*
** ------- Preprocessor directives -------
*/ 
#include "Epoch.hh"
#include "Constants.hh"
#include <cmath>	// for std::floor()
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
	assert( _year >= 1901 && _year <= 2099 );
	assert( _month >= 1 && _month <= 12 );
	assert( _day >= 1 && _day <= 31 );
	assert( _utc >= 0.0 && _utc < 24.0 );

	// populate julian date parameters and GMST
	update( 0.0 );
}

void Epoch::update(const double& dt)
{
	_utc += dt / 3600.0;

	// update Julian date
	_JD0 = ( 1'721'013.5 + 367 * _year - std::floor( ( 7.0 / 4.0 ) 
			 * ( _year + std::floor( ( _month + 9.0 ) / 12.0 ) ) )
			 + std::floor( 275.0 * _month / 9.0 ) + _day );
	_JD = _JD0 + _utc / 24.0;
	_MJD = _JD - 2'400'000.5;

	// update centuries since J2000
	_T0 = ( _JD0 - 2'451'545.0 ) / 36'525.0;
	_T1 = ( _JD - 2'451'545.0 ) / 36'525.0;
}
