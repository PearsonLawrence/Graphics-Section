#include "graphics/Load.h"
#include "graphics/RendererObjects.h"

#define STB_IMAGE_IMPLEMENTATION
#include"STB\stb_image.h"

#define TINYOBJLOADER_IMPLEMENTATION
#include "OBJ/tiny_obj_loader.h"

#include "graphics/Vertex.h"
Texture loadTexture(const char* path)
{
	Texture retval = { 0 };
	int w, h, c;
	unsigned char* pixels;

	stbi_set_flip_vertically_on_load(true);

	pixels = stbi_load(path, &w, &h, &c, STBI_default);


	retval = MakeTexture(w, h, c, pixels);

	stbi_image_free(pixels);

	return retval;
}

#include <fstream>
#include <string>
Shader loadShader(const char * vpath, const char * fpath)
{
	Shader retval = {0};

	std::string vsource;
	std::string fsource;

	std::string fileloc1 = vpath;
	std::string fileloc2 = fpath;

	std::string line;

	std::ifstream location1;
	std::ifstream location2;

	location1.open(fileloc1);
	location2.open(fileloc2);

	if (location1.is_open())
	{
		while ((std::getline(location1, line)))
		{
			vsource += line + '\n';

		}
	}

	if (location2.is_open())
	{
		while ((std::getline(location2, line)))
		{
			fsource += line + '\n';

		}
	}

	location1.close();
	location2.close();

	retval = MakeShader(vsource.c_str(), fsource.c_str());

	return retval;
}

glm::vec4 randColor()
{
	return{ rand() / (float)RAND_MAX, rand() / (float)RAND_MAX, rand() / (float)RAND_MAX, 1 };
}

Geometry loadGeometry(const char * path)
{

	Geometry retval = { 0 };
	
	tinyobj::attrib_t attrib;					//Vertex Data is stored.
	std::vector<tinyobj::shape_t> shapes;		//Triangular data, indices.
	std::vector<tinyobj::material_t> materials;	//paths to textures
	std::string err;

	tinyobj::LoadObj(&attrib, &shapes, &materials, &err, path);


	size_t isize = shapes[0].mesh.indices.size();
	size_t* indices = new unsigned[isize];

	size_t vsize = isize;
	Vertex* verts = new Vertex[vsize];

	for (int i = 0; i < isize; i++)
	{
		indices[i] = i;

		int pi = shapes[0].mesh.indices[i].vertex_index;
		int ni = shapes[0].mesh.indices[i].normal_index;
		int ti = shapes[0].mesh.indices[i].texcoord_index; //UV

		const float* p = &attrib.vertices[pi * 3];   // 3x
		const float* n = &attrib.normals[ni * 3];	   // 3x
		const float* t = &attrib.texcoords[ti*2];  // 2x

		verts[i].position = { p[0],p[1],p[2],1 };
		verts[i].UV = { t[0],t[1] };
		verts[i].normals  = { n[0],n[1],n[2],0 };
	}



	retval = makeGeometry(verts, vsize, indices, isize);
	delete[] verts;
	delete[] indices;
	return retval;
}
/*
non-interleaved:

[ppppp][nnnnn][ttttt]

[pnt][pnt][pnt][pnt][pnt]
*/