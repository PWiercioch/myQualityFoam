#include "mySkewness.H"

void mySkewness::innerLoop()
{
	forAll(cellInst,faceIndex)
	{
		faceI = faceIndex;
		
		breaking = false; // requires reset with every loop
		
		faceInst=mesh->faces()[cellInst[faceI]];
		
		dimensionCheck();
	}
}

void mySkewness::dimensionLoop(label dirI)
{
	if(mag(mesh->faces()[cellInst[faceI]].unitNormal(mesh->points())[dirI])==0) // if current normal vector component = 0
	{	
		goto breaking; // simple break statement didn't work correctly 
	}
	else
	{
		
		if((mag(mesh->faces()[cellInst[faceI]].unitNormal(mesh->points())[dirI])!=0) && ((mesh->solutionD()[dirI]==1))) // if surface normal vector parallel to slution direction
		{
		}else if((mag(mesh->faces()[cellInst[faceI]].unitNormal(mesh->points())[dirI])<0.01)) // additional condidition for very small values
		{
		}
		else
		{
			calculations();
		}
	}
	
	breaking: ;
}

void mySkewness::calculations()
{
	// for law of cosines
	point start1;
	point start2;
	point end1;
	point end2;
	
	scalar minS;
	scalar maxS;
	scalar maxAngle;
	scalar minAngle;
	
	for(label edgeI=0; edgeI<faceInst.size(); edgeI++)
	{

		if(edgeI==faceInst.size()-1) // last edge creates a pair with first one - allowed by this condidition
		{
			start2=faceEdgeCords(faceInst, 0, 0);
			end2=faceEdgeCords(faceInst, 0, 1);
		}else
		{
			start2=faceEdgeCords(faceInst, edgeI+1, 0);
			end2=faceEdgeCords(faceInst, edgeI+1, 1);
		}	
		start1=faceEdgeCords(faceInst, edgeI, 0);
		end1=faceEdgeCords(faceInst, edgeI, 1);
		
		scalar dlugosc1 = length(start1,end1);
		scalar dlugosc2 = length(start2,end2);
		
		scalar dlugoscCounter = length(end2,start1);
		
		scalar kat=angle(dlugosc1,dlugosc2,dlugoscCounter);
		
		faceAngles.append(kat);
	}
					
		minAngle=min(faceAngles);
		maxAngle=max(faceAngles);
						
		minS=minSkew(minAngle);
		maxS=maxSkew(maxAngle);
						
		if (minS>=maxS)
		{
			cellList.append(minS);
		}else
		{
			cellList.append(maxS);
		}
						
		faceAngles.clear();
						
		breaking = true;
}


point mySkewness::faceEdgeCords(face f, label index, label nodeN)
{
	point cords;
	cords.x()=mesh->points()[f.edges()[index][nodeN]].x();
	cords.y()=mesh->points()[f.edges()[index][nodeN]].y();
	cords.z()=mesh->points()[f.edges()[index][nodeN]].z();

	return cords;
}

scalar mySkewness::length(point p1, point p2)
{
	double test = Foam::sqrt(pow((p1.x()-p2.x()),2)+pow((p1.y()-p2.y()),2)+pow((p1.z()-p2.z()),2));
	
	return test; 
}

scalar mySkewness::angle(scalar l1,scalar l2,scalar l3)
{
	scalar dupa=180/3.1416*(std::acos((pow(l1,2)+pow(l2,2)-pow(l3,2))/(2*l1*l2)));
	
	return dupa;
}

scalar mySkewness::minSkew(scalar angle) 
{
	scalar x;
	if (faceInst.size()==4) x=90;
	else x=60;
	return (x-angle)/(x);
}

scalar mySkewness::maxSkew(scalar angle) 
{
	scalar x;
	if (faceInst.size()==4) x=90;
	else x=60;
	return (angle-x)/(180-x);
}

void mySkewness::qualityMetric()
{
	quality.append(max(cellList));
	
	cellList.clear();
}
