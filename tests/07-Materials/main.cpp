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
	Vertex vquad[] = {
		{ { -1,-1,0,1 },{},{ 0,0 },{ 0,0,1,0 } },
		{ { 1,-1,0,1 },{},{ 1,0 } ,{ 0,0,1,0 } },
		{ { 1, 1,0,1 },{},{ 1,1 } ,{ 0,0,1,0 } },
		{ { -1,1,0,1 },{},{ 0,1 } ,{ 0,0,1,0 } } };

	unsigned quadidx[] = { 0,1,3,1,2,3 };

	solveTangents(vquad, 6, quadidx, 4);
	Geometry quad = makeGeometry(vquad, 4, quadidx, 6);


	Texture Anime_Normal = loadTexture("../../resources/textures/kawaii_Normal.png");
	Texture floor = loadTexture("../../resources/textures/floor.png");



	Shader standard = loadShader("../../resources/shaders/standard.vert", "../../resources/shaders/standard.frag");


	Framebuffer screen = { 0,800, 900 };

	glm::mat4 cam_view = glm::lookAt(glm::vec3(0, 3, -4),
		glm::vec3(0, 1, 0),
		glm::vec3(0, 1, 0));

	glm::mat4 camproj = glm::perspective(45.f, 800.f / 600.f, .01f, 100.f);

	glm::mat4 model;

	glm::vec3 light_direction = glm::normalize(glm::vec3(1, -1, 1));
	
	while (context.step())
	{
		float time = context.getTime();

		clearFramebuffer(screen);
		setFlags(RenderFlag::DEPTH);

		model = glm::rotate(time, glm::vec3(0, 1, 0))
			* glm::rotate(glm::radians(-90.f), glm::vec3(-1, 0, 0))
			* glm::scale(glm::vec3(5, 5, 1));


		int loc = 0, slot = 0;
		setUniforms(standard, loc, slot, camproj, cam_view, model, Anime_Normal,floor, light_direction);


		s0_draw(screen, standard, quad);

	}
	
	context.Terminate();
	return 0;
}