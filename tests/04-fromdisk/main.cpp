#include "graphics\draw.h"
#include "graphics\Vertex.h"
#include "graphics\RendererObjects.h"
#include "graphics\Context.h"
#include "graphics\Load.h"
#include <iostream>
#include <random>

#include "glm/ext.hpp"

int main()
{
	Context context;

	context.init(800, 900);

	Texture tex = loadTexture("../../resources/textures/Walking.jpg");

	Vertex vquad[] = {
		{ { -.1,-.1,0,1 },{},{ 0,0 } },
		{ { .1,-.1,0,1 },{},{ 1,0 } },
		{ { .1, .1,0,1 },{},{ 1,1 } },
		{ { -.1,.1,0,1 },{},{ 0,1 } } };

	unsigned quadidx[] = { 0,1,3,1,2,3 };
	Geometry quad = makeGeometry(vquad, 4, quadidx, 6);
	Geometry cube = loadGeometry("../../resources/models/cube.obj");

	const char* vsource =
		"#version 450\n"
		"layout(location = 0) in vec4 position;\n"
		"layout(location = 2) in vec2 texCoord;\n"
		"out vec2 vUV;\n"
		"void main ()\n"
		"{ gl_Position = position; vUV = texCoord; }\n";

	const char* fsource =
		"#version 450\n"
		"out vec4 outColor;\n"
		"in vec2 vUV;\n"
		"layout(location = 0) uniform sampler2D map;\n"
		"void main () { outColor = texture(map, vUV.xy); }\n";

	Shader s = loadShader("../../resources/shaders/test.vert", 
							"../../resources/shaders/test.frag");

	Framebuffer screen = { 0, 800, 900};

	glm::vec2 RowsCols = { 9,8 };
	int idx = 1;
	while (context.step())
	{
		idx = (int)(context.getTime() * 4) ;
		clearFramebuffer(screen);

		int index = 0, tsloet = 0;
		setUniforms(s, index, tsloet, tex,idx, RowsCols);

		s0_draw(screen, s, cube);

		// You glorious weeb

	}

	context.Terminate();
	return 0;
}