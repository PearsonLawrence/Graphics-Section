#include "graphics\GameObjects.h"
#include "graphics\Vertex.h"
#include "graphics\Load.h"
#include "glm\ext.hpp"
#include "graphics\Context.h"
#include "graphics\draw.h"
#include <iostream>
#include <vector>
#include "glm\glm.hpp"

// Std. Includes
#include <string>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


void main()
{
	Context context;
	context.init(1280, 720);

	std::vector<std::string> faces
	{
		"../../resources/textures/stormydays_ft.tga",
		"../../resources/textures/stormydays_bk.tga",
		

		"../../resources/textures/stormydays_up.tga",
		"../../resources/textures/stormydays_dn.tga",

		"../../resources/textures/stormydays_rt.tga",
		"../../resources/textures/stormydays_lf.tga",
			
	};

	Geometry  sky_geo = loadGeometry("../../resources/models/cube.obj");
	Skybox    sky_map = loadCubemap(faces);
	glm::mat4 sky_model = glm::scale(glm::vec3(20,20,20));
	Shader	  sky_shader = loadShader("../../resources/shaders/Skybox.vert", "../../resources/shaders/Skybox.frag");
	
	// Camera
	Camera cam;
	cam.view;// = glm::lookAt(glm::vec3(0, 2, 5), glm::vec3(0, 1, 0), glm::vec3(0, 1, 0));
	cam.proj = glm::perspective(45.f, 1280.f / 720.f, 1.f, 100.f);

	Framebuffer screen = { 0,1280,720 };


	int loc = 0, slot = 0;
	while (context.step())
	{
		float time = context.getTime();

		sky_model = glm::rotate(time*1.0f, glm::vec3(0,1,0)) * glm::scale(glm::vec3(20, 20, 20));

		clearFramebuffer(screen);
		setFlags(RenderFlag::DEPTH);
		loc = slot = 0;

		setUniforms(sky_shader, loc, slot, cam.proj, cam.view, sky_model, sky_map);
		s0_draw(screen, sky_shader, sky_geo);
	}
	context.Terminate();
}