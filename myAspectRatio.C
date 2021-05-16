#include "myAspectRatio.H"

void myAspectRatio::innerLoop()
{
	cellList.clear();
	forAll(cellInst.edges(mesh->faces()),edgeIndex)
	{
		edgeI = edgeIndex; // allows use inside functions
		dimensionCheck();
	}
}

void myAspectRatio::dimensionLoop(label dirI)
{
	edgeNumber.clear();
	if(edgeNumber.find(edgeI)==-1)
	{
		if(mag(cellInst.edges(mesh->faces())[edgeI].unitVec(mesh->points())[dirI])==0) // if any edge vector componet = 0
		{	
			goto breaking; // simple break statement didn't work correctly 
		else{
		if((mag(cellInst.edges(mesh->faces())[edgeI].unitVec(mesh->points())[dirI])>0.0001)&&(mesh->solutionD()[dirI])==-1) //jesli wektor krawedzi jest w danym kierunku(wiekszy od malej liczby) i ten kierunek jest eempty 
		{
		}else 
		{
			calculations();
		}
		}
	
	breaking: ;
}

void myAspectRatio::calculations()
{
	cellList.append(cellInst.edges(mesh->faces())[edgeI].mag(mesh->points())); // append to single cell edge length list
	edgeNumber.append(edgeI);
}

void myAspectRatio::qualityMetric() // find min and max length; append their ratio to list containing results
{
	scalar minLength=min(cellList);
	scalar maxLength=max(cellList);
	
	quality.append(maxLength/minLength);
	
	cellList.clear();
}
