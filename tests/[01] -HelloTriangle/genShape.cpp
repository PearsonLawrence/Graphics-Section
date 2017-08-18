#include "graphics\RendererObjects.h"
#include "graphics\Vertex.h"
#include "genShape.h"
#include <cmath>

#define PI 3.14159265359

Geometry makeNGon(int SideCount, float radius)
{

		unsigned vsize = SideCount + 1;
		unsigned isize = (SideCount * 3);
		Vertex* verts = new Vertex[vsize];
		unsigned* idx = new unsigned[isize];

		float CurrentAngle = 0;
		float MaxAngle = 360;
		

		
		for (int i = 1; i < vsize; i++)
		{
			float currentAngleToRad = CurrentAngle * PI / 180.0f;
			float x = cos(currentAngleToRad) * radius;
			float y = sin(currentAngleToRad) * radius;
			verts[i] = { glm::vec4{ x, y, 0, 1}, {1.0,0.0,0.0,1.0} };
			CurrentAngle += 360 / SideCount;
   	    }
		verts[0] = { glm::vec4{ 0, 0, 0, 1 },{ 1.0,1.0,0.0,1.0 } };
		
		int j = 0;
		int offset = 0;
		for (int i = 0; i < isize; i++)
		{
			if (i != isize - 1)
			{
				if (j == 3)
				{
					idx[i] = 0;
					j = 0;
					offset += 2;
				}
				else
				{
					idx[i] = (i - offset);
				}
			}
			else
			{
				idx[i] = 1;
			}
			j++;
		}
		Geometry ret = makeGeometry(verts, vsize, idx, isize);

		delete[] verts;
		delete[] idx;
	
	
		return ret;
}

Geometry MakeCheckerboard(int dim, float size)
{
	
	unsigned vsize = (dim + 1) * (dim + 1);
	unsigned isize = 3 * 2 * dim * dim;
	Vertex* verts = new Vertex[vsize];
	unsigned* idx = new unsigned[isize];
	
	float step = dim / size;

	for (int i = 0; i < 16; i++)
	{
		float y = i * step;
		for (int j = 0; j < dim + 1; j++)
		{
			float x = j * step;
		}
	}
	
	Geometry ret = makeGeometry(verts, vsize, idx, isize);

	delete[] verts;
	delete[] idx;


	return ret;

}
