#include "graphics\RendererObjects.h"
#include "graphics\draw.h"
#include "glinc.h"
#include "glm\glm.hpp"
#include <glm/gtc/type_ptr.hpp>

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

void setUniform(const Shader & s, int location, float value)
{
	glProgramUniform1f(s.handle, location, value);

}

void setUniform(const Shader & s, int location, int value)
{
	glProgramUniform1i(s.handle, location, value);

}

void setUniform(const Shader & s, int location, const glm::vec4 &value)
{
	glProgramUniform4fv(s.handle, location, 1, glm::value_ptr(value));
}

void setUniform(const Shader & s, int location, const Texture & value, unsigned slot)
{
	glActiveTexture(GL_TEXTURE0 + slot);
	glBindTexture(GL_TEXTURE_2D, value.handle);

	glProgramUniform1i(s.handle, location, slot);
}

void clearFramebuffer(const Framebuffer & fb)
{
	glBindFramebuffer(GL_FRAMEBUFFER,fb.handle);
	glClear(GL_COLOR_BUFFER_BIT);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}
