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
		{ { -.1,-.1,0,1 },{},{ 0,0 } },
		{ { .1,-.1,0,1 },{},{ 1,0 } },
		{ { .1, .1,0,1 },{},{ 1,1 } },
		{ { -.1,.1,0,1 },{},{ 0,1 } } };

	unsigned quadidx[] = { 0,1,3,1,2,3 };

	Geometry ss_geo = loadGeometry("../../resources/models/soulspear.obj");
	Texture ss_diffuse = loadTexture("../../resources/textures/soulspear_diffuse.tga");
	Geometry sphere_geo = loadGeometry("../../resources/models/sphere.obj");
	Texture sphere_diffuse = loadTexture("../../resources/textures/blood.jpg");
	Shader mvplite		= loadShader("../../resources/Shaders/mvplite.vert",
									 "../../resources/Shaders/mvplite.frag");

	Framebuffer screen = { 0,800, 900 };
	
	float prevTime = 0;
	float speed = 1.2f;
	glm::vec3 position = {0,1,20};
	int verticle, horizontal;
	while (context.step())
	{
		float ct = context.getTime();
		float dt = ct - prevTime;
		prevTime = ct;

		if (context.getKey('W')) {verticle = context.getKey('W');}
		else if (context.getKey('S')) {verticle = -context.getKey('S');}
		else if (context.getKey('A')) {horizontal = context.getKey('A');}
		else if (context.getKey('D')) {horizontal = -context.getKey('D');}
		else { verticle = 0; horizontal = 0; }
		glm::vec3 input = { (dt * 2) * horizontal, (dt * 2) *verticle,0 };

		 position += input ;

		glm::mat4 cam_view = glm::lookAt(glm::vec3(0, 3, -4), position, glm::vec3(0, 1, 0));
		glm::mat4 cam_proj = glm::perspective(45.f, 800.f / 900.f, .01f, 100.f);

		glm::mat4 go_model = glm::translate(position) *
							 glm::rotate(ct * 2, glm::vec3(0, 1, 0)); // identity matrix for now
		glm::mat4 go_model2 = glm::translate(glm::vec3(2, -2, 5)) *
			glm::rotate(ct * .5f, glm::vec3(0, 1, 0)); // identity matrix for now
		glm::mat4 go_model3 = glm::translate(glm::vec3(-2, -2, 5)) *
			glm::rotate(ct * .5f, glm::vec3(0, 1, 0));// identity matrix for now
		glm::mat4 go_model4 = glm::translate(glm::vec3(2, -2, -5)) *
			glm::rotate(ct * .5f, glm::vec3(0, 1, 0));// identity matrix for now
		glm::mat4 go_model5 = glm::translate(glm::vec3(-2, -2, -5)) *
			glm::rotate(ct * .5f, glm::vec3(0, 1, 0));// identity matrix for now
		glm::mat4 go_model6 = glm::translate(glm::vec3(5, -2, 0)) *
			glm::rotate(ct * .5f, glm::vec3(0, 1, 0)); // identity matrix for now
		glm::mat4 go_model7 = glm::translate(glm::vec3(-5, -2, 0)) *
			glm::rotate(ct * .5f, glm::vec3(0, 1, 0)); // identity matrix for now

		
		clearFramebuffer(screen);
		setFlags(RenderFlag::DEPTH);

		int index = 0, tsloet = 0;
		setUniforms(mvplite, index, tsloet,
			cam_proj, cam_view, go_model, ss_diffuse);

		s0_draw(screen, mvplite, ss_geo);

		index = 0, tsloet = 0;
		setUniforms(mvplite, index, tsloet,
			cam_proj, cam_view, go_model * go_model2, sphere_diffuse);
		s0_draw(screen, mvplite, sphere_geo);

		index = 0, tsloet = 0;
		setUniforms(mvplite, index, tsloet,
			cam_proj, cam_view, go_model * go_model3, sphere_diffuse);
		s0_draw(screen, mvplite, sphere_geo);

		index = 0, tsloet = 0;
		setUniforms(mvplite, index, tsloet,
			cam_proj, cam_view, go_model * go_model4, sphere_diffuse);
		s0_draw(screen, mvplite, sphere_geo);

		index = 0, tsloet = 0;
		setUniforms(mvplite, index, tsloet,
			cam_proj, cam_view, go_model * go_model5, sphere_diffuse);
		s0_draw(screen, mvplite, sphere_geo);

		index = 0, tsloet = 0;
		setUniforms(mvplite, index, tsloet,
			cam_proj, cam_view, go_model * go_model6, sphere_diffuse);
		s0_draw(screen, mvplite, sphere_geo);

		index = 0, tsloet = 0;
		setUniforms(mvplite, index, tsloet,
			cam_proj, cam_view, go_model * go_model7, sphere_diffuse);
		s0_draw(screen, mvplite, sphere_geo);



	}
	freeTexture(ss_diffuse);
	context.Terminate();
	return 0;
}