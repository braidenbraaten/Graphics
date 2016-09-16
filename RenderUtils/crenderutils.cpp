//#include "gldecs.h"
//#include "globjs.h"
//#include "crenderutils.h"
//#include <cstdio>
//
//#include "glm\gtc\noise.hpp"
//#define STB_IMAGE_IMPLEMENTATION
//#include "stb_image.h"
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//void draw(const Shader &shader, const Geometry &geometry)
//{
//	glUseProgram(shader.handle);
//
//	//binding the VAO also binds the IBO(tri) and VBO( verts)
//	glBindVertexArray(geometry.vao);
//
//	//Draw elements will draw the vertices that are currently bound
//	//using an array of indeces.
//	//IF AN IBO IS BOUND, we don't need to provide any indices.
//	glDrawElements(GL_TRIANGLES, geometry.size, GL_UNSIGNED_INT, 0);
//
//}
//
//void draw(const Shader &shader, const Geometry &geometry, float time)
//{
//	glUseProgram(shader.handle);
//	glBindVertexArray(geometry.vao);
//	
//
//	//    WIREFRAME MODE
//	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
//
//	//gets the location index number of the time variable   -1 = failed
//	int loc = glGetUniformLocation(shader.handle, "time");
//	//makes sure that the time passed in is set for the time var in the shader
//	glUniform1f(loc, time);
//
//	glDrawElements(GL_TRIANGLES, geometry.size, GL_UNSIGNED_INT, 0);
//}
//
//void draw(const Shader &s, const Geometry &g,
//	const float M[16], const float V[16], const float P[16], float time)
//{
//
//	glEnable(GL_CULL_FACE);
//	glEnable(GL_DEPTH_TEST); //testing Z depth
//
//							 //makes it WIREFRAME
//							 //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
//	glUseProgram(s.handle);
//	glBindVertexArray(g.vao);
//
//	glUniformMatrix4fv(0, 1, GL_FALSE, P);
//	glUniformMatrix4fv(1, 1, GL_FALSE, V);
//	glUniformMatrix4fv(2, 1, GL_FALSE, M);
//
//	glUniform1f(3, time);
//
//
//	glDrawElements(GL_TRIANGLES, g.size, GL_UNSIGNED_INT, 0);
//}
//
//
//
//	void drawPhong(const Shader &s, const Geometry &g,
//	const float M[16], const float V[16], const float P[16])
//{
//
//	glEnable(GL_CULL_FACE);
//	glEnable(GL_DEPTH_TEST); //testing Z depth
//
//							 //makes it WIREFRAME
//							 //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
//	glUseProgram(s.handle);
//	glBindVertexArray(g.vao);
//
//	glUniformMatrix4fv(0, 1, GL_FALSE, P);
//	glUniformMatrix4fv(1, 1, GL_FALSE, V);
//	glUniformMatrix4fv(2, 1, GL_FALSE, M);
//
//
//
//
//	glDrawElements(GL_TRIANGLES, g.size, GL_UNSIGNED_INT, 0);
//}
//
//	void drawPhong(const Shader & s, const Geometry & g, 
//		const float M[16], const float V[16], const float P[16],
//		const Texture *T, unsigned t_count)
//	{
//
//		glEnable(GL_CULL_FACE);
//		glEnable(GL_DEPTH_TEST); //testing Z depth
//
//								 //makes it WIREFRAME
//								 //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
//		glUseProgram(s.handle);
//		glBindVertexArray(g.vao);
//
//		glUniformMatrix4fv(0, 1, GL_FALSE, P);
//		glUniformMatrix4fv(1, 1, GL_FALSE, V);
//		glUniformMatrix4fv(2, 1, GL_FALSE, M);
//
//
//		for (int i = 0; i < t_count; ++i)
//		{
//			glActiveTexture(GL_TEXTURE0 + i);
//			glBindTexture(GL_TEXTURE_2D, T[i].handle);
//			glUniform1i(3 + i, 0 + i);
//		}
//
//		glDrawElements(GL_TRIANGLES, g.size, GL_UNSIGNED_INT, 0);
//
//
//	}
//
//	void drawFB(const Shader & s, const Geometry & g, const Framebuffer & fb,
//		const float M[16], const float V[16], const float P[16],
//		const Texture * T, unsigned t_count)
//	{
//		glEnable(GL_CULL_FACE);
//		glEnable(GL_DEPTH_TEST); //testing Z depth
//
//		glBindFramebuffer(GL_FRAMEBUFFER, fb.handle);
//		glUseProgram(s.handle);
//		glBindVertexArray(g.vao);
//
//		glViewport(0, 0, fb.width, fb.height);
//
//		glUniformMatrix4fv(0, 1, GL_FALSE, P);
//		glUniformMatrix4fv(1, 1, GL_FALSE, V);
//		glUniformMatrix4fv(2, 1, GL_FALSE, M);
//
//		int i = 0;
//		for (; i < t_count; ++i)
//		{
//			glActiveTexture(GL_TEXTURE0 + i);
//			glBindTexture(GL_TEXTURE_2D, T[i].handle);
//			glUniform1i(3 + i, 0 + i);
//		}
//
//		glDrawElements(GL_TRIANGLES, g.size, GL_UNSIGNED_INT, 0);
//
//	}
//
//void draw(const Shader &s, const Geometry &g, const Texture &t,
//						const float M[16], const float V[16], const float P[16], float time)
//{
//
//	glEnable(GL_CULL_FACE);
//	glEnable(GL_DEPTH_TEST); //testing Z depth
//	
//	//makes it WIREFRAME
//	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
//	glUseProgram(s.handle);
//	glBindVertexArray(g.vao);
//
//	glUniformMatrix4fv(0, 1, GL_FALSE, P);
//	glUniformMatrix4fv(1, 1, GL_FALSE, V);
//	glUniformMatrix4fv(2, 1, GL_FALSE, M);
//
//	glUniform1f(3, time);
//
//	glActiveTexture(GL_TEXTURE0); // look at slot 0
//	glBindTexture(GL_TEXTURE_2D, t.handle); //put it in that slot
//	glUniform1i(4, 0); //second value is texture slot number 
//
//	glDrawElements(GL_TRIANGLES, g.size, GL_UNSIGNED_INT, 0);
//}
//
//
//
//
//
//void clearFramebuffer(const Framebuffer &f)
//{
//	glBindFramebuffer(GL_FRAMEBUFFER, f.handle);
//	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//
//}
//
//#include <string.h>
//#include <fstream>
//#include <istream>
//
//
//
//
//
////#define TINYOBJLOADER_IMPLEMENTATION // define this in only one .cc
//#include"OBJ\tiny_obj_loader.h"
//#include <random>
//
//
