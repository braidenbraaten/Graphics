#include "crenderutils.h"
#include "window.h"
#include "Gallery.h"
#include "Timer.h"
#include "Input.h"
#include "globjects.h"
#include "Camera.h"

#include "glm\glm.hpp"
#include "glm\ext.hpp"
#include "procgen.h"

int main()
{
	Window window;
	Gallery gallery;

	Input input;
	
	window.init(1280, 720);
	//position of eye, center of eye looking position, the up for the eye (usually the Y)
	glm::mat4 view = glm::lookAt(glm::vec3(3.f,4.f,6.f), glm::vec3(0.f,4.f,0.f), glm::vec3(0.f,1.f,0.f));
	glm::mat4 proj = glm::perspective(45.f, 16/9.f, 1.f, 100.f);
	glm::mat4 modelC, modelS;

	Geometry cube = loadOBJ("../res/models/soulspear.obj");
	Shader shader = loadShader("../res/shaders/phongVert.txt", 
							   "../res/shaders/phongFrag.txt");
	Texture tarray[] = {loadTexture("../res/textures/soulspear_diffuse.tga")};



	//Geometry sphere = loadOBJ("../res/models/Bunny.obj");

	//Geometry bunny = loadOBJ("../res/models/Bunny.obj");
	float  time = 0;
	//   UPDATE SECTION
	while (window.step())
	{
		
		time += .016f;
		glm::mat4 modelC = glm::rotate(time / 100, glm::normalize(glm::vec3(0, 1, 0)));
		//glm::mat4 modelS = glm::translate(glm::vec3(0, cos(time) * 6, 0));
		drawPhong(shader, cube, glm::value_ptr(modelC),
							   glm::value_ptr(view),
							   glm::value_ptr(proj), tarray, 1);

		//drawPhong(shader, sphere, glm::value_ptr(modelS),
		//	glm::value_ptr(view),
		//	glm::value_ptr(proj));

		
	}
	window.term();

	return 0;
}