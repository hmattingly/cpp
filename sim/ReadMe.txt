------- Framework --------
MATH : file that contains various math constants, classes, and functions
	Angle
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

---- Integrator Set Up ----
1. Instantiate Integrator -> constructor calls Scheduler::registerIntegrator() to add Integrator to array
2. Instantiate Model -> constructor calls registerState() which adds reference to variables to an array. 
	Think about how to keep track of array. Work uses IntegratorData class. 
		IntegratorData has member variables: model pointer, integrator pointer, double State array (max 128), double dState array (max 128), num elements in State
	registerState() should accept double state, double dstate or overload Vector3 state, Vector3 dstate. It should instantiate IntegratorData (if decide to use this)
3. pIntegrator -> registerModel(pModel) for each model
	registerModel() should...
		a. check if the model has already been registered to an integrator:
			If yes, error and exit
			If no, update flag in model to indicate it is registered with integrator
		b. add model.IntegratorData to IntegratorData array
		c. if model is not initialized, run initModel()
---- Integrator Update ----	
Scheduler::update() loops through each integrator and calls Integrator -> calcModels() and Integrator -> advanceStates()
	Integrator::calcModels() loops through IntegratorData array then performs IntegratorData->pModel->calcModel() which computes derivatives of States (consider instead looping through each registered Model)
	Integrator::advanceStates() loops through IntegratorData array and performs RK2 or RK4 integration to update each element in IntegratorData then performs IntegratorData->pModel->updateStates() which just updates other variables in the model now that the state is up to the current time step
	
