#ifndef MYSKEWNESS
#define MYSKEWNESS
#include "myQuality.H"
#include <cmath>

class myAspectRatio;
class mySkewness :public myQuality
{
	private: 
		
	List<scalar> faceAngles; // face angles list
	
	face faceInst; // temp face definition
	
	label faceI;
	
	bool breaking; // loop breaking in 2d analysis
	
	virtual void innerLoop();
	
	virtual void dimensionLoop(label dirI);
	
	virtual void calculations();
	
	virtual void qualityMetric();
	
	point faceEdgeCords(face f, label index, label nodeN); // returns vertex coordinates
	
	scalar angle(scalar l1,scalar l2,scalar l3); // angle calculation based on law of cosines
	
	scalar length(point p1, point p2); // compute length from 2 points
	
	scalar minSkew(scalar angle); // compute skewness for face min angle
	
	scalar maxSkew(scalar angle); // compute skewness for face max angle
	
	public:
	
	using myQuality::myQuality; // allows use of constructor
	
	friend void combine(mySkewness s, myAspectRatio er); // friend declaration
	
};
#endif // MYSKEWNESS
