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

// reference definitions
  // O = Center of Earth
  // B = Center of Mass of Body
// frame definitions
  // N = ECI
  // E = ECEF
  // P = Perifocal
  // L = LVLH / RTN

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

	void setL2N(const double& inc, const double& raan, const double& aol);
	void setN2L(const double& inc, const double& raan, const double& aol);
	void setP2N(const double& inc, const double& raan, const double& aop);
	void setN2P(const double& inc, const double& raan, const double& aop);
	void setE2N(Earth* pEarth);
	void setN2E(Earth* pEarth);
	
};

#endif  // FRAMETRANSFORM_HH
