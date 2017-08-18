#include "graphics\RendererObjects.h"
#include "graphics\draw.h"
#include "glinc.h"

void s0_draw(const Framebuffer &f, const Shader &s, const Geometry &g)
{
	//what are we using
	glBindFramebuffer(GL_FRAMEBUFFER, f.handle);
	glUseProgram(s.handle);
	glBindVertexArray(g.handle);

	//what area of the framebuffer do we draw to
	glViewport(0, 0, f.width, f.height);

	//draw it 
	glDrawElements(GL_TRIANGLES, g.size,GL_UNSIGNED_INT,0);

	// unbind if you want
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glUseProgram(0);
	glBindVertexArray(0);
}