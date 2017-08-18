
#include "graphics\Context.h"
#include <iostream>
#include "graphics\RendererObjects.h"
#include "graphics\Vertex.h"
#include "graphics\Draw.h"
#include "genShape.h"

int main()
{
	Context context;
	context.init();

	Vertex verts[4] = { {{-.5f,-.5f,0,1},{1.0, 0.0,0.0,1.0}},
						{{.5f,-.5f,0,1},{ 1.0, 1.0,0.0,1.0 } },
						{{ .5f ,.5f,0,1},{ 1.0, 0.0,1.0,1.0 } },
						{{ -.5f ,.5f,0,1},{ 0.0, 1.0,1.0,1.0 } } };

	unsigned idxs[6] = { 0,1,2,3,2,0 };
	Geometry g = makeGeometry(verts, 4, idxs, 6);
	Geometry k = makeNGon(100,.5f);
	Geometry l = MakeCheckerboard(5, 5, .1f);

	const char* vsource =
		"#version 450\n"
		"layout(location = 0) in vec4 position;\n"
		"layout(location = 1) in vec4 color;\n"
		"out vec4 vPos;\n"
		"out vec4 vColor;\n"
		"void main ()\n"
		"{\n"
		"gl_Position = position;"
		"vPos = position;\n"
		"vColor = color;\n"
		"}\n";

	const char* fsource =
		"#version 450\n"
		"out vec4 outColor;\n"

		"in vec4 vPos;\n"
		"in vec4 vColor;\n"
		"void main () { outColor = vColor; }\n";

	Shader s = MakeShader(vsource, fsource);

	Framebuffer f = { 0,800,600 };

	while ((context.step())) // Game Loop
	{
		s0_draw(f, s, g);

		s0_draw(f, s, k);
	}

	freeGeometry(g);
	freeShader(s);

	context.Terminate();
	return 0;
}