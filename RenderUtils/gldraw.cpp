#include "gldecs.h"
#include "gldraw.h"

void ClearFramebuffer(const Framebuffer & r)
{
	glBindFramebuffer(GL_FRAMEBUFFER, r.handle);
	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
}

void tdraw_internal::tdraw_begin(const Shader & s, const Geometry & g, const Framebuffer & r)
{
	glBindFramebuffer(GL_FRAMEBUFFER, r.handle);
	glUseProgram(s.handle);
	glBindVertexArray(g.vao);


	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);
	glViewport(0, 0, r.width, r.height);
}

void tdraw_internal::tdraw_close(const Shader & s, const Geometry & g, const Framebuffer & r)
{
	//reset everything so it can be used elsewhere / once again

	glDrawElements(GL_TRIANGLES, g.size, GL_UNSIGNED_INT, 0);

	glBindVertexArray(0);
	glUseProgram(0);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	//int w, h;
	//glfwGetFramebufferSize(glfwGetCurrentContext(), &w, &h);

	//glViewport(0, 0, w, h);

}
