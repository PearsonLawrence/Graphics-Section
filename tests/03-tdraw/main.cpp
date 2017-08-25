#include "graphics\draw.h"
#include "graphics\Vertex.h"
#include "graphics\RendererObjects.h"
#include "graphics\Context.h"

#include <iostream>
#include <random>

#include "glm/ext.hpp"
int main()
{
	Context context;
	context.init();

	Vertex verts[4] = { { { -.1f,-.1f,0,1 },{ 1,1,0,1 },{ 0,0 } },
	{ { .1f,-.1f,0,1 },{ 0,1,1,1 },{ 1,0 } },
	{ { .1f ,.1f,0,1 },{ 1,0,1,1 },{ 1,1 } },
	{ { -.1f ,.1f,0,1 },{ 0,1,0,1 },{ 0,1 } } };

	unsigned idxs[6] = { 0,1,2,3,2,0 };
	Geometry g = makeGeometry(verts, 4, idxs, 6);
	double x = 0, y = 0;

	const char* vsource =
		"#version 450\n"
		"layout(location = 0) in vec4 position;\n"
		"layout(location = 2) in vec2 UV;\n"
		"layout(location = 5) uniform mat4 model;"
		"out vec2 vUV;\n"
		"void main ()\n"
		"{\n"
		"gl_Position = model * position;"
		"vUV = UV;\n"
		"}\n";

	const char* fsource =
		"#version 450\n"
		"out vec4 outColor;\n"
		"layout(location = 0) uniform sampler2D map;\n"
		"layout(location = 1) uniform float time;\n"
		"layout(location = 2) uniform int key;"
		"layout(location = 3) uniform int key2;"
		"layout(location = 4) uniform int key3;"

		"vec4 Red = {1,0,0,1};\n"
		"vec4 Green = {0,1,0,1};\n"
		"vec4 Blue = {0,0,1,1};\n"

		"in vec2 vUV;\n"
		"void main () {"
		"outColor =  texture(map,vUV) * sin(time);"
		"outColor += Red * key;\n "
		"outColor += Green * key2;\n "
		"outColor += Blue * key3;\n "
		"}\n";

	//"outColor = 2 * key - texture(map,vUV) * sin(time);"

	Shader s = MakeShader(vsource, fsource);

	Framebuffer f = { 0,800,600 };


	//RGB texture (3 channels), 2x1,
	unsigned char pixels[] = { 0,255,128,255,
								0,128,255,0,
								0,255,128,255,
								0,128,255,0 };



	Texture t_magyel = MakeTexture(3, 1, 3, pixels); //magenta and yellow
	Texture t_mask = MakeTexture(4, 4, 1, pixels);

	while ((context.step())) // Game Loop
	{
		clearFramebuffer(f);
		glm::mat4 mod1 = glm::translate(glm::vec3(.5, 0, 0)) *
							glm::rotate((float)context.getTime(), glm::vec3(0, 0, 1));

		glm::mat4 rot = glm::rotate((float)context.getTime(), glm::vec3(0, 0, 1));

		int loc = 0, tex = 0;
		setUniforms(s, loc, tex, t_magyel, (float)context.getTime(), (int)context.getKey('A'), 
			(int)context.getKey('S'), (int)context.getKey('D'),rot*mod1);
		s0_draw(f, s, g);
		
		int loc1 = 0, tex1 = 0;
		setUniforms(s, loc1, tex1, t_magyel, (float)context.getTime(), (int)context.getKey('A'), 
			(int)context.getKey('S'), (int)context.getKey('D'), rot);
		s0_draw(f, s, g);
	}

	freeGeometry(g);
	freeShader(s);
	freeTexture(t_magyel);
	freeTexture(t_mask);
	context.Terminate();
	return 0;
}