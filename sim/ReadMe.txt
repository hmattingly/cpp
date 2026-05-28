------- Framework --------
MATH : file that contains various math constants, classes, and functions
	Angle
		deg2rad() : deg to radians
		rad2deg()
		deg2arc() : deg to deg + arcmin + arcsec
		arc2deg()
		e2ta() : eccentric anomaly to true anomaly
		ta2e()
		e2m() : eccentric anomaly to mean anomaly
		m2e()
		ta2m() : true anomaly to mean anomaly
		m2ta()
	Vector
		magnitude()
		unit()
	Matrix
		eigenvalues()
		eigenvectors()
		trace()
		determinant()
		inverse()
	dot()
	cross()
	multiply()

State:
	Spacecraft : holds the state elements and body characteristics of spacecraft. Can be integrated
			
	CelestialBody : Holds all parameters related to a particular celetial body
		Earth
		Moon
		Sun
	
	Observer : holds an Earth observer position. Can be integrated
		gdLat() : geodetic latitude
		gcLat() : geocentric latitude
		altitude()
		longitude()
		lmst() : local mean sidereal time
		hourAngle() : local hour angle

	Range : holds the range between two objects. Can be integrated Can be integrated
		azimuth()
		elevation()
		rightAscension()
		declination()

Transforms : provides the transformation matrix between various frames
	eci2kep() : ECI to keplerian orbital elements
	eci2ecef() : ECI to ECEF 
	eci2equi() : ECI to modified equinoctial orbital elements
	eci2mil() : ECI to Milankovitch orbital elements
	eci2rtn() : ECI to RTN
	kep2eci()
	kep2ecef()
	kep2equi()
	kep2mil()
	kep2rtn()

Epoch : holds time characteristics. Can be integrated
	utc() : hour time in UTC
	date() : year, month, day, time (UTC)\
	et() : seconds since J2000
	t0() : mod centuries since J2000
	t1() : centuries since J2000
	gmst() : Greenwich mean sidereal time
	jd() : Julian date
	mjd() : modified Julian date

Dynamics: include dynamic models for natural and non-naturally occurring forces
	TwoBodyDynamics
	NBodyDynamics : allows inclusion of Sun and Moon
	J2Dynamics
	J3Dyanmics
	J4Dynamics
	SrpDynamics: allows inclusion of solar radiation pressure
	DragDynamics
	ControlInput

Integrator : given a time step, updates the current state based on active dynamic models
	ForwardEuler
	BackwardEuler
	RK2 : Runge-Kutta 2
	RK4 : Runge-Kutta 4

SimManager : runs the simulation by repeatedly calling the integrator(s), handles stop conditions, logs data and events, etc.
	Scheduler : handles clock 
	EventManager : handles scheduling and recording events throughout simulation
	Logger() : logs info, events, warnings, and errors
