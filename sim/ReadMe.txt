TODO:
	Matrix
		eigenvalues()
		eigenvectors()
		inverse()

	Spacecraft
		add switch if state provided in orbital elements. Use updateFromKepOE() in SpacecraftBody

	Moon
		add position vector given epoch
	Sun
		add position vector given epoch

	CoordinateTransform
		I2eqoe: ECI to modified equinoctial orbital elements (and vice versa)
		I2miloe: ECI to Milankovitch orbital elements (and vice versa)

	Dynamics
		SRPDynamics
		SunDynamics
		MoonDynamics
		ControlInput

	Integrator
		Periodic Execution
		BackwardEuler
		RK2 : Runge-Kutta 2

------ Definitions ------
All vectors require the following definitions:
	1. Type of vector (e.g. position, velocity, angular momentum, etc)
	2. Type of object it points to (e.g. spacecraft body, Sun, Moon, observer, etc)
	3. Reference point or reference frame
		For position vectors, this is a reference to a frame origin
		For derivative vectors (e.g. velocity) this is a reference to a frame
	4. Resolved frame
All vectors follow the following format:
	<vector type> of <object it points to> with respect to <reference> expressed in <resolved frame>
Vector magnitudes end with "mag" and do not require a resolved frame but do require a reference
Unit vectors end with "hat"

Vector type definitions
	R = position
	V = velocity
	A = acceleration
	W = angular velocity
	E = eccentricity
	H = specific angular momentum
	N = line of nodes
Origin definitions
	C = Center of Earth
	S = Center of Sun
	M = Center of Moon
	B = Center of Body
	O = Center of Observer
Frame definitions
	I = ECI
	E = ECEF
	P = Perifocal
	L = LVLH / RTN
	T = topocentric (SEZ / SEU)
	N = NED
Examples
	RofBwrtCexpI = position of body from center of Earth expressed in ECI
	VofOwrtEexpN = velocity of observer with respect to ECEF expressed in NED
	WofEwrtIexpE = angular velocity of ECEF frame with respect to ECI expressed in ECEF
