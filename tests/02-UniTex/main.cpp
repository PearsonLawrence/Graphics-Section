#include "graphics\draw.h"
#include "graphics\Vertex.h"
#include "graphics\RendererObjects.h"
#include "graphics\Context.h"

#include <iostream>
#include <random>
int main()
{
	Context context;
	context.init();

	Vertex verts[4] = { { { -.5f,-.5f,0,1 },{ 1,1,0,1}, {0,0} },
	{ { .5f,-.5f,0,1 },{ 0,1,1,1 },{ 1,0 } },
	{ { .5f ,.5f,0,1 },{ 1,0,1,1},{ 1,1 } },
	{ { -.5f ,.5f,0,1 },{0,1,0,1 },{ 0,1 } } };

	unsigned idxs[6] = { 0,1,2,3,2,0 };
	Geometry g = makeGeometry(verts, 4, idxs, 6);
	double x = 0, y = 0;

	const char* vsource =
		"#version 450\n"
		"layout(location = 0) in vec4 position;\n"
		"layout(location = 1) in vec4 color;\n"
		"layout(location = 2) in vec2 UV;\n"
		"layout(location = 0) uniform float time;\n"
		"layout(location = 1) uniform float pressX;\n"
		"layout(location = 3) uniform float pressY;\n"
		"layout(location = 2) uniform vec4 Mouseposition;\n"
		"out vec4 vPos;\n"
		"out vec4 vColor;\n"

		"out vec2 vUV;\n"
		"void main ()\n"
		"{\n"
		"gl_Position = position;"
		"vPos = position;\n"
		"vColor = color;\n"
		/*"vColor.y += cos(time * gl_Position.x);"/*
		"gl_Position.x += cos(pressX + gl_Position.y);\n"
		"gl_Position.y += sin(pressY + gl_Position.x);\n"*/
		"gl_Position += Mouseposition;\n"
		//"gl_Position.x += sin(Mouseposition.x + gl_Position.y);"
		//"gl_Position.y += cos(Mouseposition.y+ gl_Position.x);"
		"vUV = UV;\n"
		"}\n";

	const char* fsource =
		"#version 450\n"
		"layout(location = 4) uniform sampler2D map;\n"
		"layout(location = 5) uniform sampler2D map2;\n"
		"layout(location = 0) uniform float time;\n"
		"out vec4 outColor;\n"
		"in float timer;\n"
		"in vec4 vPos;\n"
		"in vec4 vColor;\n"
		"in vec2 vUV;\n"
		"void main () {"
		"vec2 uv = vUV;\n"
		"uv +=  2 * sin(2 * time + uv.x) + uv.y;\n"
		"outColor = texture(map,uv) * texture(map2, uv).r;"
		"}\n";

	Shader s = MakeShader(vsource, fsource);

	Framebuffer f = { 0,800,600 };


	//RGB texture (3 channels), 2x1,
	unsigned char pixels[] = { 255,0,255,
							  255,255,0 };

	int RandColorAmount = 10;// rand() % 20 + 1;
	//unsigned char pixelsTwo[RandColorAmount] = { };

	unsigned char *pixies = new unsigned char[RandColorAmount];

	for (int i = 0; i < RandColorAmount; i++)
	{
		int randR = rand() % 255;

		pixies[i] = randR;
	}

	

	Texture t_magyel = MakeTexture(4, 1, 1, pixels); //magenta and yellow
	Texture t_mask = MakeTexture(RandColorAmount, 4, 3, pixies); //magenta and yellow

	delete[] pixies;

	//int timeSinceStart = glutGet(GLUT_ELAPSED_TIME);
	float prevTime = 0;
	float speed = 1.2f;
	while ((context.step())) // Game Loop
	{
		double ct = context.getTime() ;
		float dt = ct - prevTime;
		prevTime = ct;
		/*y += context.getKey('W') * dt * speed;

		x -= context.getKey('A') * dt * speed;

		y -= context.getKey('S')  * dt * speed;

		x += context.getKey('D')  * dt * speed;
*/
		context.getMousePosition(x, y);
		clearFramebuffer(f);
		x = 2 * (x / 800) - 1;
		y = 1 - 2 * (y / 600);

		/*
		setUniform(s, 1, (float)x);
		setUniform(s, 3, (float)y);*/
		setUniform(s, 0, (float)context.getTime());
		setUniform(s, 2, (glm::vec4)glm::vec4{x,y,0,0});
		setUniform(s, 4, t_magyel, 0);

		setUniform(s, 5, t_mask, 1);


		s0_draw(f, s, g);
		
	}

	freeGeometry(g);
	freeShader(s);
	freeTexture(t_magyel);
	freeTexture(t_mask);
	context.Terminate();
	return 0;
}