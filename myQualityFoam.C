#include "myQualityFoam.H"

// +++++++++++++++++++++++
// MAIN FILE
// +++++++++++++++++++++++

int main(int argc, char *argv[])
{
    #include "setRootCase.H"
    #include "createTime.H"
    #include "createMesh.H"
	
	
	// Create text files in time directory
	volScalarField myEdgeRatio
	{
		IOobject
		(
			"myEdgeRatio",
		    runTime.timeName(),
		    mesh,
		    IOobject::NO_READ,
		    IOobject::AUTO_WRITE
		),
		mesh,
		dimensionedScalar("myEdgeRatio", dimless, scalar(0.0))// allows automatic file creation
	};
	
	volScalarField mySkew
	{
		IOobject
		(
			"mySkew",
		    runTime.timeName(),
		    mesh,
		    IOobject::NO_READ,
		    IOobject::AUTO_WRITE
		),
		mesh,
		dimensionedScalar("mySkew", dimless, scalar(0.0))
	};
	
	volScalarField myQualityMetric
	{
		IOobject
		(
			"myQualityMetric",
		    runTime.timeName(),
		    mesh,
		    IOobject::NO_READ,
		    IOobject::AUTO_WRITE
		),
		mesh,
		dimensionedScalar("myQualityMetric", dimless, scalar(0.0))
	};
	
	meshInfo(mesh);
	Info<<endl;
	
	myAspectRatio AR(mesh);
	mySkewness skew(mesh);
	
	AR.cellLoop();
	skew.cellLoop();
	
	combine(skew,AR);
	
	writeData(AR.showQuality(), myEdgeRatio);
	writeData(skew.showQuality(), mySkew);
	writeData(combinedMetric, myQualityMetric);
	
	sectionBreak();
	Info<<"MESH QUALITY"<<endl;
	sectionBreak();
	Info<<endl;
	Info<<"Component metrics"<<endl;
	sectionBreak();
	
	displayInfo(skew.showQuality(), "Skewness", mesh,false);
	Info<<endl;
	displayInfo(AR.showQuality(), "Aspect Ratio", mesh,false);
	
	Info<<endl<<endl<<"Combined metric"<<endl;
	sectionBreak();
	displayInfo(combinedMetric, "combined metric", mesh,true);
	if(limitSize.size()>0)
	{
		volScalarField outOfRange
		{
			IOobject
			(
				"outOfRange",
				runTime.timeName(),
				mesh,
				IOobject::NO_READ,
				IOobject::AUTO_WRITE
			),
			mesh,
			dimensionedScalar("outOfRange", dimless, scalar(0.0))
		};
	
		writeData(overTheLimit, outOfRange);
		
		Info<<endl;
		Info<<"No. of cells out of range: "<<limitSize.size()<<endl;
		sectionBreak();
		Info<<endl;
	}
	
	Info<<endl;
	sectionBreak();
	Info<<"TIME"<<endl;
	sectionBreak();
	Info<< "ExecutionTime = " << runTime.elapsedCpuTime() << " s" << nl 
	<< "ClockTime = " << runTime.elapsedClockTime() << " s" <<endl<<endl;
	
	return 0;
}
