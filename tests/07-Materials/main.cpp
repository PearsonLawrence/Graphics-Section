#include "graphics\draw.h"
#include "graphics\Vertex.h"
#include "graphics\RendererObjects.h"
#include "graphics\Context.h"
#include "graphics\Load.h"
#include <iostream>
#include <random>

#include "graphics\GameObjects.h"

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

	SpecGloss sceneObjects[2];
	sceneObjects[0].geo = loadGeometry("../../resources/models/soulspear.obj");

	sceneObjects[0].normal = loadTexture("../../resources/textures/soulspear_normal.tga");
	sceneObjects[0].diffuse = loadTexture("../../resources/textures/soulspear_diffuse.tga");
	sceneObjects[0].specular = loadTexture("../../resources/textures/soulspear_specular.tga");
	sceneObjects[0].gloss = 4.0f;

	SpecGloss Cube;

	sceneObjects[1].geo = loadGeometry("../../resources/models/cube.obj");

	sceneObjects[1].model = glm::rotate(glm::radians(90.f), glm::vec3(0, 0, 1));

	sceneObjects[1].normal = loadTexture("../../resources/textures/soulspear_normal.tga");
	sceneObjects[1].diffuse = loadTexture("../../resources/textures/soulspear_diffuse.tga");
	sceneObjects[1].specular = loadTexture("../../resources/textures/soulspear_specular.tga");


	Shader standard = loadShader("../../resources/shaders/standard.vert", "../../resources/shaders/standard.frag");
	Shader fsq_shader = loadShader("../../resources/shaders/Quad.vert", "../../resources/shaders/Quad.frag");


	Framebuffer screen = { 0,800, 900 };

	// Float textures are not playing nicely.
	Framebuffer fBuffer = makeFramebuffer(800, 900, 4, true, 3, 1);

	Camera cam;

	cam.view = glm::lookAt(glm::vec3(0, 2, 3),
									 glm::vec3(0, 2, 0),
									 glm::vec3(0, 1, 0));

	cam.proj = glm::perspective(45.f, 800.f / 600.f, 1.8f, 4.f);

	glm::mat4 model;

	StandardLight light;
	light.direction = glm::normalize(glm::vec3(1,0 , -1));
	light.color	  = glm::vec4(.7,.6,.9,1);
	light.intensity	  = 5.0f;
	light.ambient	  = glm::vec4(.2,.2,.01,1);
	light.type		  = 0;

	while (context.step())
	{
		float time = context.getTime();

		clearFramebuffer(fBuffer);
		setFlags(RenderFlag::DEPTH);

		model = glm::rotate(time, glm::vec3(0, 1, 0))
			* glm::scale(glm::vec3(1, 1, 1));


		int loc = 0, slot = 0;

		for (int i = 0; i < 2; i++)
		{
			setUniforms(standard, loc, slot, cam.proj, cam.view, model,
				sceneObjects[i].diffuse, sceneObjects[i].specular, sceneObjects[i].normal, sceneObjects[i].gloss, light.direction, light.color
				, light.intensity, light.ambient, light.type);
			s0_draw(fBuffer, standard, sceneObjects[i].geo);
		}
		

		clearFramebuffer(screen);
		loc = 0, slot = 0;
		setUniforms(fsq_shader, loc, slot, fBuffer.targets[1], fBuffer.targets[2]);
		s0_draw(screen, fsq_shader, quad);
	}
	
	context.Terminate();
	return 0;
}