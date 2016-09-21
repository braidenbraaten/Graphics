
#include "crenderutils.h"
#include "glm\ext.hpp"
int main()
{
	Window window;
	window.init(1280,720);

	Geometry quad = makeGeometry(quad_verts, 4, quad_tris, 6);
	Geometry spear = loadOBJ("../res/models/soulspear.obj");


	Shader simple = loadShader("../res/shaders/simple.vert", "../res/shaders/simple.frag");
	Shader post = loadShader("../res/shaders/post.vert", "../res/shaders/post.frag");
	Shader gpass = loadShader("../res/shaders/gpass.vert", "../res/shaders/gpass.frag");

	Texture spear_normal = loadTexture("../res/textures/soulspear_normal.tga");
	Texture spear_diffuse = loadTexture("../res/textures/soulspear_diffuse.tga");
	Texture spear_specular = loadTexture("../res/textures/soulspear_specular.tga");

	Framebuffer screen = { 0,1280,720 };
	Framebuffer frame = makeFramebuffer(1280, 720, 2);

	glm::mat4 model, view, proj;

	model = glm::translate(glm::vec3(1, 0, 0));
	view = glm::lookAt(glm::vec3(1, 1, 5), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
	proj = glm::perspective(45.f, 1280.f / 720, 1.f, 100.f);

	float time = 0;
	while (window.step())
	{
		time += 0.016f;
		ClearFramebuffer(frame);

		model = glm::rotate(time, glm::vec3(0, 1, 0)) * glm::translate(glm::vec3(0, -1, 0));

		tdraw(simple, spear, screen, model, view, proj,
			  spear_diffuse, spear_normal, spear_specular);


		tdraw(post, quad,screen, frame.colors[0], frame.colors[1]);
	}

	window.term();
}