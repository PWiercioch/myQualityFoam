#include "myQuality.H"

class mySkewness;
class myAspectRatio :public myQuality
{
	private: 
	
	label edgeI;
	
	List<label> edgeNumber; // used for skipping unecessary computation in 2D
	
	virtual void innerLoop();
	
	virtual void dimensionLoop(label dirI);
	
	virtual void calculations();
	
	virtual void qualityMetric();
	
	public:
	
	using myQuality::myQuality; // allows use of parent class constructor
	
	friend void combine(mySkewness s, myAspectRatio er); // friend declaration
	
};
