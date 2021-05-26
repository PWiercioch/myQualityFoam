#include "fvCFD.H"
#include "myQuality.H"
#include "mySkewness.H"
#include "myAspectRatio.H"

List<scalar> combinedMetric;
List<scalar> overTheLimit;
List<label> limitSize;

void sectionBreak()
{
	Info<<"-----------------------------------------------------------------------------------------"<<endl;
}

void combine(mySkewness s,myAspectRatio er) // cell quality model
{
	scalar result;
	forAll(s.quality,index)
	{	
		// Quadratic function
		//result=1.075 -0.04954 * er.quality[index] -0.2972 * s.quality[index] + 0.001249 * pow(er.quality[index],2) + 0.00292 * er.quality[index] * s.quality[index] - 0.2816 * pow(s.quality[index],2);
		
		// Logarithmic component
		result=1.031 - 0.004635 * er.quality[index] - 0.2972 * s.quality[index] + 0.00292 * er.quality[index] * s.quality[index] - 0.1218 * std::log(er.quality[index]) - 0.2816 * pow(s.quality[index],2);
		if(result>1) 
		{
			result=1;
			overTheLimit.append(0);
		}
		else if(result<0) 
		{
			overTheLimit.append(1);
			result=0;
			limitSize.append(1);
		}
		else overTheLimit.append(0);
		combinedMetric.append(result);
	}
}

void meshInfo(fvMesh& mesh)
{
	sectionBreak();
	Info<< "MESH STATISTICS" << endl;
	sectionBreak();
	Info<<endl<<"Mesh has "<<mesh.nSolutionD()<<" solutions: "<<mesh.solutionD()<<endl<<endl
	<< "Cell count: " << mesh.cells().size() << nl
	<< "Face count: " << mesh.faces().size() << nl
	<< "Node count: " << mesh.points().size() << nl;
	Info<<endl;
};

scalar average(List<scalar> list)
{
	scalar suma=0;
	forAll(list, index)
	{
		suma=suma+list[index];
	}
	
	return suma/list.size();
}

void displayInfo(List<scalar> jakosc, string nazwa, fvMesh& mesh, bool combinedBool) // print onfo to console
{	
	label minQ, maxQ;
	
	if(combinedBool==false)
	{
		minQ=findMin(jakosc);
		maxQ=findMax(jakosc);
	}else
	{
		minQ=findMax(jakosc);
		maxQ=findMin(jakosc);
	}

	cout<<"Worst value of "<<nazwa<<": "<<jakosc[maxQ];
	Info<<" in cell No. "<<maxQ<<" in "<<mesh.C()[maxQ]<<nl;
	cout<<"Best value of "<<nazwa<<": "<<jakosc[minQ];
	Info<<" in cell No. "<<minQ<<" in "<<mesh.C()[minQ]<<nl;
	cout<<nl<<"Mean value of "<<nazwa<<": "<<average(jakosc)<<nl<<nl;
}

void writeData(List<scalar> list, volScalarField file) // insert data to volScalarField
{
	for(int cellI=0;cellI<list.size();cellI++)
	{
		file[cellI]=list[cellI];
	}
	file.write();
}
