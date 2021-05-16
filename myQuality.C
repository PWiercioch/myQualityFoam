#include "myQuality.H"

myQuality::myQuality(fvMesh& m)
{
	mesh=&m;
}

void myQuality::cellLoop()
{
	forAll(mesh->cells(),cellI)
	{
	 cellInst=mesh->cells()[cellI];
	 innerLoop();
	 
	 qualityMetric();

	}
}

void myQuality::dimensionCheck()
{
	if(mesh->nSolutionD()==2)
	{
		forAll(mesh->solutionD(),dirI)
		{
			label dirIndex=dirI;
			dimensionLoop(dirIndex);
		}
	}else
	{
		calculations();
	}
}
