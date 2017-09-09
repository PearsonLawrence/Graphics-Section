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


	Framebuffer screen = { 0,800, 900 };
	//Scene

	//floor
	Vertex vquad[] =
	{
		{{-1,-1,0,1},{},{0,0},{0,0,1,0}},
		{{1,-1,0,1},{},{1,0},{0,0,1,0}},
		{{1, 1,0,1},{},{1,1},{0,0,1,0}},
		{{-1, 1,0,1},{},{0,1},{0,0,1,0}}
	};
	
	unsigned quadidx[] = { 0,1,3,1,2,3 };
	solveTangents(vquad, 4, quadidx, 6);

	Geometry floor_geo = makeGeometry(vquad, 4, quadidx, 6);

	glm::mat4 floor_model = glm::rotate(glm::radians(90.f), glm::vec3(-1, 0, 0))
						  * glm::scale(glm::vec3(5, 5, 1));

	Geometry ss_geo = loadGeometry("../../resources/models/soulspear.obj");
	glm::mat4 ss_model; // = glm::rotate(time,glm::vec3(0,1,0)) // on update.

	Geometry cube_geo = loadGeometry("../../resources/models/cube.obj");
	glm::mat4 cube_model = glm::translate(glm::vec3(2, 1, -1));

	glm::mat4 cam_view = glm::lookAt(glm::vec3(0, 1, 5),
									 glm::vec3(0, 1, 0),
									 glm::vec3(0, 1, 0));

	glm::mat4 cam_proj = glm::perspective(45.f, (float)screen.width / (float)screen.height, 1.f, 10.f);

	//light
	glm::vec3 light_dir = glm::normalize(glm::vec3(.8, -1, -1));
	glm::mat4 light_proj = glm::ortho<float>(-10, 10, -10, 10, -10, 10);
	glm::mat4 light_view = glm::lookAt(-light_dir, glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));

	glm::vec3 light_dir2 = glm::normalize(glm::vec3(.6, -2, 1));
	glm::mat4 light_proj2 = glm::ortho<float>(-10, 10, -10, 10, -10, 10);
	glm::mat4 light_view2 = glm::lookAt(-light_dir2, glm::vec3(10, 5, 10), glm::vec3(0, 5, 0));

	//shaders
	Shader shdr_shadow = loadShader("../../resources/Shaders/shadow.vert",
		"../../resources/Shaders/shadow.frag");
	Shader shdr_direct = loadShader("../../resources/Shaders/direct.vert",
		"../../resources/Shaders/direct.frag");

	

	Framebuffer fb_shadow = makeFramebuffer(2048, 2048, 0, true, 0, 0);

	glm::vec4 Yellow = glm::vec4(1, 1, 0, 1);
	glm::vec4 Red = glm::vec4(1, 0, 0, 1);

	while (context.step())
	{
		float time = context.getTime();
		ss_model = glm::rotate(time, glm::vec3(0, 1, 0)); // on update.
		clearFramebuffer(fb_shadow, false, true);
		setFlags(RenderFlag::DEPTH);

		int loc = 0, slot = 0;
		setUniforms(shdr_shadow, loc, slot, light_proj, light_view, floor_model);
		s0_draw(fb_shadow, shdr_shadow, floor_geo);


		loc = slot = 0;
		setUniforms(shdr_shadow, loc, slot, light_proj, light_view, ss_model);
		s0_draw(fb_shadow, shdr_shadow, ss_geo);


		loc = slot = 0;
		setUniforms(shdr_shadow, loc, slot, light_proj, light_view, cube_model);
		s0_draw(fb_shadow, shdr_shadow, cube_geo);

	

		clearFramebuffer(screen);
		setFlags(RenderFlag::DEPTH);

		loc = slot = 0;

		setUniforms(shdr_direct, loc, slot, cam_proj, cam_view, floor_model, light_proj, light_view, fb_shadow.depthTarget, Yellow, light_proj2,light_view2,Red);
		s0_draw(screen, shdr_direct, floor_geo);

		loc = slot = 0;

		setUniforms(shdr_direct, loc, slot, cam_proj, cam_view, ss_model, light_proj, light_view, fb_shadow.depthTarget, Yellow, light_proj2, light_view2, Red);
		s0_draw(screen, shdr_direct, ss_geo);

		loc = slot = 0;

		setUniforms(shdr_direct, loc, slot, cam_proj, cam_view, cube_model, light_proj, light_view, fb_shadow.depthTarget, Yellow, light_proj2, light_view2, Red);
		s0_draw(screen, shdr_direct, cube_geo);
		
		

	}

	context.Terminate();
	return 0;
}