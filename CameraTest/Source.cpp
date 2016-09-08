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
	Timer time;
	Input input;
	
	//Has to be the first thing to init, because it creates the window
	window.init(1280, 720);
	
	gallery.init();
	input.init(window);
	time.init();
	//yellow color
	unsigned char pixels[] = {255,255,0};
	Texture tex = loadTexture("../res/textures/textureTest.jpg");

	//Vertex verts[] = { { 1,1,0,1 },{ 1,-1,0,1 },{ -1,-1,0,1 },{ -1,1,0,1 } };

	unsigned tris[6] = { 0, 5, 2,   1, 4, 5 };
	gallery.loadObjectOBJ("CUBE", "../res/models/cube.obj");
	gallery.loadObjectOBJ("SPHERE", "../res/models/sphere.obj");


	gallery.loadShader("SIMPLE", "../res/shaders/simpleVert.txt",
		"../res/shaders/simpleFrag.txt");

	gallery.loadShader("CAMERA", "../res/shaders/cameraVert.txt",
		"../res/shaders/cameraFrag.txt");
	gallery.loadShader("TEXTURE", "../res/shaders/texVert.txt",
		"../res/shaders/texFrag.txt");


	glm::mat4 proj, view, model, model2, model3;

	//   GRID
	Geometry plane = genGrid(800, 2);
	Texture noise = genNoise(512, 2);

			//x,x,y,y
	//proj = glm::ortho<float>(-10, 10, -10, 10, -10, 10);
	proj = glm::perspective(45.f, 1.f, 1.f, 50.f);
	
	model2 = glm::translate(glm::vec3(1, 0, 1)) * glm::rotate(180.f, glm::vec3(0, -1, 0));
	
	float dt = 0;

	model3 = glm::translate(glm::vec3(-10, 0, 0)) * glm::rotate(180.f, glm::vec3(0, 1, 0)) * glm::scale(glm::vec3(5, 5, 5));

	
	
	float ct = 0;

	FlyCamera cam;
	cam.jumpTo(glm::vec3(0, 0, -10));
	cam.lookAt(glm::vec3(0, 0, 0));

	//   UPDATE SECTION
	while (window.step())
	{
		
		time.step();
		input.step();
		
		ct += time.getDeltaTime();
		view = cam.getView();
		proj = cam.getProjection();


		cam.update(input, time);

		model = glm::translate(glm::vec3(0, ct, 0)) *
			glm::rotate(ct, glm::vec3(0, 1, 0));
		//draw(gallery.getShader("SIMPLE"), gallery.getObject("CUBE"), time);


		//Draw each of the objects with the corrisponding shader



		draw(gallery.getShader("TEXTURE"), gallery.getObject("CUBE"), tex,
			glm::value_ptr(model), glm::value_ptr(view), glm::value_ptr(proj),ct );

		draw(gallery.getShader("TEXTURE"), gallery.getObject("CUBE"), tex, 
			glm::value_ptr(model2), glm::value_ptr(view), glm::value_ptr(proj),ct);

		draw(gallery.getShader("TEXTURE"), gallery.getObject("SPHERE"),
			glm::value_ptr(model3), glm::value_ptr(view), glm::value_ptr(proj),ct);

		//draw(gallery.getShader("TEXTURE"), plane, tex, 
		//	glm::value_ptr(model3), glm::value_ptr(view), glm::value_ptr(proj), ct);
		draw(gallery.getShader("TEXTURE"), plane, noise,
			glm::value_ptr(model3), glm::value_ptr(view), glm::value_ptr(proj), ct);
		
	}
	freeTexture(tex);
	//terminate when done
	input.term();
	time.term();
	gallery.term();
	window.term();

	return 0;
}