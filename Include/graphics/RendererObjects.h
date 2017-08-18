#pragma once

struct  Vertex;
struct Geometry
{
	unsigned handle, // Vertex array object
			 vbo,    // vertex buffer
			 ibo,    // Index Buffer
			 size;   // how many indicies make up this model
};

Geometry makeGeometry(const Vertex* vertices, size_t vsize,
	                  const unsigned* indicies, size_t isize);

void freeGeometry(Geometry &g);



struct Shader
{
	unsigned handle;
};

Shader MakeShader(const char* vert_src, const char* frag_src);

void freeShader(Shader &s);

struct Framebuffer
{
	unsigned handle,
			 width, 
			 height;
};