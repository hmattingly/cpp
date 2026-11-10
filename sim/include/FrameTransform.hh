/*
** ------------ Header Guard -------------
*/ 
#ifndef FRAMETRANSFORM_HH  
#define FRAMETRANSFORM_HH

/*
** ------- Preprocessor directives -------
*/ 
#include "Matrix.hh"

/*
** -------------- Constants ---------------
*/ 

/*
** -------- Forward Declarations ----------
*/ 


/*
** --------- Namespace directives ---------
*/ 
class Earth;

/*
** ----------- Class Definition ------------
*/ 

class FrameTransform
{
	Matrix3 _dcm { IDENTITY_MATRIX3 };

public:
	// default constructor
	FrameTransform() = default;

	// parameterized constructor
	FrameTransform(const Matrix3& dcm);

	// destructor
	~FrameTransform() = default;

	// forward declarations
	static const Matrix3 getRot1(const double& theta);
	static const Matrix3 getRot2(const double& theta);
	static const Matrix3 getRot3(const double& theta);

	// access functions
	Matrix3 getDCM() const { return _dcm; }

	// setter functions
	void setEulerAngles121(const double& phi, const double& theta, const double& psi);
	void setEulerAngles123(const double& phi, const double& theta, const double& psi);
	void setEulerAngles131(const double& phi, const double& theta, const double& psi);
	void setEulerAngles132(const double& phi, const double& theta, const double& psi);
	void setEulerAngles212(const double& phi, const double& theta, const double& psi);
	void setEulerAngles213(const double& phi, const double& theta, const double& psi);
	void setEulerAngles231(const double& phi, const double& theta, const double& psi);
	void setEulerAngles232(const double& phi, const double& theta, const double& psi);
	void setEulerAngles312(const double& phi, const double& theta, const double& psi);
	void setEulerAngles313(const double& phi, const double& theta, const double& psi);
	void setEulerAngles321(const double& phi, const double& theta, const double& psi);
	void setEulerAngles323(const double& phi, const double& theta, const double& psi);

	void setEulerAngles12(const double& phi, const double& theta);
	void setEulerAngles21(const double& phi, const double& theta);
	void setEulerAngles13(const double& phi, const double& theta);
	void setEulerAngles31(const double& phi, const double& theta);
	void setEulerAngles32(const double& phi, const double& theta);
	void setEulerAngles23(const double& phi, const double& theta);

	// LVLH to ECI
	void setL2I(const double& inc, const double& raan, const double& aol);

	// ECI to LVLH
	void setI2L(const double& inc, const double& raan, const double& aol);

	// Perifocal to ECI
	void setP2I(const double& inc, const double& raan, const double& aop);

	// ECI to Perifocal
	void setI2P(const double& inc, const double& raan, const double& aop);

	// NED to ECI
	void setN2I(const double& gdLat, const double& st);

	// ECI to NED
	void setI2N(const double& gdLat, const double& st);

	// Topocentric (SEZ) to ECI
	void setT2I(const double& gdLat, const double& st);

	// ECI to Topocentric (SEZ)
	void setI2T(const double& gdLat, const double& st);

	// ECEF to ECI
	void setE2I(Earth* pEarth);

	// ECI to ECEF
	void setI2E(Earth* pEarth);

	// NED to ECEF
	void setN2E(const double& gdLat, const double& lon);

	// ECEF to NED
	void setE2N(const double& gdLat, const double& lon);
	
	// Topocentric (SEZ) to ECEF
	void setT2E(const double& gdLat, const double& lon);

	// ECEF to Topocentric (SEZ)
	void setE2T(const double& gdLat, const double& lon);

	// NED to Topocentric (SEZ)
	void setN2T();

	// Topocentric (SEZ) to NED
	void setT2N();
	
};

#endif  // FRAMETRANSFORM_HH
