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

	Texture tex = loadTexture("../../resources/textures/sun.jpg");
	Texture tex2 = loadTexture("../../resources/textures/earth.jpg");

	Vertex vquad[] = {
		{ { -.1,-.1,0,1 },{},{ 0,0 } },
		{ { .1,-.1,0,1 },{},{ 1,0 } },
		{ { .1, .1,0,1 },{},{ 1,1 } },
		{ { -.1,.1,0,1 },{},{ 0,1 } } };

	unsigned quadidx[] = { 0,1,3,1,2,3 };
	Geometry quad = makeGeometry(vquad, 4, quadidx, 6);
	Geometry cube = loadGeometry("../../resources/models/sphere.obj");

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

	//Shader s = loadShader("../../resources/shaders/test.vert", 
							//"../../resources/shaders/test.frag");
	Shader scube = loadShader("../../resources/shaders/cube.vert",
							  "../../resources/shaders/cube.frag");
	Shader planet2 = loadShader("../../resources/shaders/cube.vert",
		"../../resources/shaders/cube.frag");

	Framebuffer screen = { 0, 800, 900};

	glm::vec2 RowsCols = { 9,8 };
	int idx = 1;

	setFlags(RenderFlag::DEPTH);
	while (context.step())
	{
		float time = context.getTime();

		idx = (int)(context.getTime() * 4) ;

		clearFramebuffer(screen);

		int index = 0, tsloet = 0;
		glm::vec4 SunPosition = {0,0,0,1};
		//setUniforms(s, index, tsloet, tex,idx, RowsCols);

		glm::mat4 mod_cube =  glm::rotate(time, glm::vec3(0, -.1, 0)) *
							  glm::scale(glm::vec3(.5, .5, .5));

		glm::mat4 mod_cube2 = glm::translate(glm::vec3(1, 0, 0)) *
							  glm::scale(glm::vec3(.1, .1, .1));

		setUniforms(scube, index, tsloet, mod_cube, tex, SunPosition);
		s0_draw(screen, scube, cube);

		index = 0, tsloet = 0;
		setUniforms(planet2, index, tsloet, mod_cube * mod_cube2, tex2, SunPosition);
		s0_draw(screen, planet2, cube);


	}

	context.Terminate();
	return 0;
}