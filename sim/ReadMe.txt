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
		N2eqoe: ECI to modified equinoctial orbital elements (and vice versa)
		N2miloe: ECI to Milankovitch orbital elements (and vice versa)

	Dynamics
		SRPDynamics
		SunDynamics
		MoonDynamics
		ControlInput

	Integrator
		Periodic Execution
		BackwardEuler
		RK2 : Runge-Kutta 2

