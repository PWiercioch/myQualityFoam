#ifndef MYQUALITY_H
#define MYQUALITY_H
#include "fvCFD.H"


class myQuality
{
	protected: 
	
	List<scalar> quality; // list of results
	
	public:
	
	List<scalar> cellList; // list of all possible cell quality scores; used to find the worst
	
	cell cellInst; // temporary container for current cell data
	
	void cellLoop(); // Most outer loop - iterates over each cell, defines currnet faceInst
	
	virtual ~myQuality()=default; // abstarct class destructor
	
	myQuality(fvMesh& m); // constructor
	
	fvMesh *mesh; // defined inside constructor
	
	virtual void innerLoop()=0; // inner loop - iterates over each of cell's edges for myAspectRatio and each cell's faces in mySkewness
	
	void dimensionCheck(); // check if analysis is 2D
	
	virtual void dimensionLoop(label dirI)=0; // if analysis 2d - iterate over each direction in face normal vector(mySkewness) or edge vector (myAspectRatio)
	
	virtual void calculations()=0; // tutaj sie dzieje najwieej obliczenmost of the calculations
	
	virtual void qualityMetric()=0; // compute cell quality
	
	List<scalar> showQuality() // allows to acces private member quality
	{
		return quality;
	}
	
};

#endif // MYQUALITY_H
