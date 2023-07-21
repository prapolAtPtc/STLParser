
#include <stdlib.h>
#include "Vertex.h"


vtx::vtx()
{
	//valid = false;
	vx = 0;
	vy = 0;
	vz = 0;
	// Default Constructor
}

vtx::vtx(const char* binFacet)
{
	if(binFacet != NULL)
	{
		char f1[4] = {binFacet[0],binFacet[1],binFacet[2],binFacet[3]};
		char f2[4] = {binFacet[4],binFacet[5],binFacet[6],binFacet[7]};
		char f3[4] = {binFacet[8],binFacet[9],binFacet[10],binFacet[11]};


		vx = *((float*) f1 );
		vy = *((float*) f2 );
		vz = *((float*) f3 );
		//valid = true;
	}
}

vtx::vtx(double x, double y, double z)
{
	vx = x;
	vy = y;
	vz = z;
	//valid = true;
}

vtx::vtx(const char* x, const char* y, const char* z)
{
	vx = strtod(x,NULL);
	vy = strtod(y,NULL);
	vz = strtod(z,NULL);
	//valid = true;
}
