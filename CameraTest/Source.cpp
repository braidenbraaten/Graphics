

#include "crenderutils.h"
#include "window.h"
#include "Input.h"
#include "Camera.h"
#include "GLM\glm.hpp"
#include "GLM\ext.hpp"
#include "Timer.h"
int main()
{
	Window	window;
	Input input;


	window.init(1280, 720);
	input.init(window);

	
	glm::mat4 view = glm::lookAt(glm::vec3(0.f, 1.5f, 3.f),  // eye
		glm::vec3(0.f, 1.5f, 0.f),  // center
		glm::vec3(0.f, 1.f, 0.f)); // up

	glm::mat4 proj = glm::perspective(45.f, 16 / 9.f, 1.f, 100.f);
	glm::mat4 modelC, modelS;

	Geometry soulspear = loadOBJ("../res/models/soulspear.obj");

	Shader   shader = loadShader("../res/shaders/phongVert.txt",
		"../res/shaders/phongFrag.txt");

	

	Texture tarray[] = { loadTexture("../res/textures/soulspear_diffuse.tga"),
		loadTexture("../res/textures/soulspear_specular.tga"),
		loadTexture("../res/textures/soulspear_normal.tga") };

	Framebuffer frame = makeFramebuffer(1280, 720, 3);
	Framebuffer screen = { 0,1280,720,1 };

	Vertex verts[] = { {{-1,-1,0,1},{},{},{0,0}},
					   {{ 1,-1,0,1},{},{},{1,0}},
					   {{ 1,1,0,1},{},{},{1,1}},
					   {{-1,1,0,1},{},{},{0,1}} };
	unsigned tris[] = {0,1,2,2,3,0};

	Shader post = loadShader("../res/shaders/postVert.txt", 
							 "../res/shaders/postFrag.txt");
	Geometry quad = makeGeometry(verts, 4, tris, 6);
	
	float time = 0.0f;

	
	while (window.step())
	{
		time += 0.016f;
		clearFramebuffer(frame);

		input.step();

		modelC = glm::rotate(time, glm::normalize(glm::vec3(0, 1, 0)));

		drawFB(shader, soulspear,frame, glm::value_ptr(modelC),
			glm::value_ptr(view),
			glm::value_ptr(proj),
			tarray, 3);

		drawFB(post, quad, screen, glm::value_ptr(glm::mat4()),
			glm::value_ptr(glm::mat4()),
			glm::value_ptr(glm::mat4()),
			frame.colors, frame.nColors);
	}

	FreeFramebuffer(frame);
	freeShader(post);
	freeShader(shader);
	freeGeometry(soulspear);
	for each(auto &t in tarray) {freeTexture(t);}

	window.term();
	return 0;
}