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

	Geometry ss_geo = loadGeometry("../../resources/models/soulspear.obj");

	Texture ss_normal = loadTexture("../../resources/textures/soulspear_normal.tga");
	Texture ss_diffuse = loadTexture("../../resources/textures/soulspear_diffuse.tga");
	Texture ss_specular = loadTexture("../../resources/textures/soulspear_specular.tga");
	float	ss_gloss = 4.0f;



	Shader standard = loadShader("../../resources/shaders/standard.vert", "../../resources/shaders/standard.frag");
	Shader fsq_shader = loadShader("../../resources/shaders/Quad.vert", "../../resources/shaders/Quad.frag");


	Framebuffer screen = { 0,800, 900 };

	// Float textures are not playing nicely.
	Framebuffer fBuffer = makeFramebuffer(800, 900, 4, true, 3, 1);

	glm::mat4 cam_view = glm::lookAt(glm::vec3(0, 2, 3),
									 glm::vec3(0, 2, 0),
									 glm::vec3(0, 1, 0));

	glm::mat4 camproj = glm::perspective(45.f, 800.f / 600.f, 1.8f, 4.f);

	glm::mat4 model;

	glm::vec3 light_direction = glm::normalize(glm::vec3(1,0 , -1));
	glm::vec4 l_color		  = glm::vec4(.7,.6,.9,1);
	float	  l_intensity	  = 5.0f;
	glm::vec4 l_ambient		  = glm::vec4(.2,.2,.01,1);
	int       l_type		  = 0;

	while (context.step())
	{
		float time = context.getTime();

		clearFramebuffer(fBuffer);
		setFlags(RenderFlag::DEPTH);

		model = glm::rotate(time, glm::vec3(0, 1, 0))
			* glm::scale(glm::vec3(1, 1, 1));


		int loc = 0, slot = 0;
		setUniforms(standard, loc, slot, camproj, cam_view, model,
			ss_diffuse, ss_specular, ss_normal, ss_gloss, light_direction, l_color
			,l_intensity,l_ambient,l_type);


		s0_draw(fBuffer, standard, ss_geo);


		clearFramebuffer(screen);
		loc = 0, slot = 0;
		setUniforms(fsq_shader, loc, slot, fBuffer.targets[1], fBuffer.targets[2]);
		s0_draw(screen, fsq_shader, quad);
	}
	
	context.Terminate();
	return 0;
}