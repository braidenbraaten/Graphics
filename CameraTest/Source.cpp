#include "window.h"
#include "crenderutils.h"
#include "Vertex.h"
#include "Gallery.h"
#include "glm\glm.hpp"
#include "glm\ext.hpp"
//this is the develop branch!

int main()
{
	Window window;
	Gallery gallery;
	//Has to be the first thing to init, because it creates the window
	window.init(600, 600);
	gallery.init();
	//clipping space coordinates
	// -1,1
	// 1920 x 1080
	Vertex vert[6] = { { .5f,0.0f, 0, 1, 1,0,0,1 },
	{ -.5f,.6f, 0, 1, 0,1,0,1 },
	{ .9f,.9f, 0, 1, 0,0,1,1 },

	{ 0.9f,0.1f,0, 1,0,1,0,1 },
	{ .2f, .1f,0, 1,1,0,0,1 },
	{ -.4f,0.3f,0, 1,1,1,1,1 } };

	unsigned tris[6] = { 0, 5, 2,   1, 4, 5 };
	Geometry geo = makeGeometry(vert, 6, tris, 6);
	float time = 0;


	float IDENTITY[16] = { 1,0,0,0, //Right
						   0,1,0,0, //Up 
						   0,0,1,0, //Forward
						   0,0,0,1};

	glm::mat4 proj, view, model, model2;
							//x,x,y,y
	//proj = glm::ortho<float>(-10, 10, -10, 10, -10, 10);
	proj = glm::perspective(45.f, 1.f, .1f, 100.f);


	//model = glm::scale(glm::vec3{ .5f,.5f,.5f }) 
	//	  * glm::translate(glm::vec3(.5f, .1f, .1f));


	while (window.step())
	{
		time += 0.03667f;

		view = glm::lookAt(glm::vec3(10.f + cosf(time) * 5, 0.f, 5.f),
						   glm::vec3(0.f, 0.f, 0.f),
						   glm::vec3(0.f, 1.f, 0.f));

		model = glm::rotate(time, glm::vec3(0, 1, 0));
		model2 = glm::translate(glm::vec3(1, 0, 1));
		//draw(gallery.getShader("SIMPLE"), gallery.getObject("CUBE"), time);
		draw(gallery.getShader("CAMERA"), gallery.getObject("CUBE"), 
			glm::value_ptr(model), glm::value_ptr(view), glm::value_ptr(proj));

		draw(gallery.getShader("CAMERA"), gallery.getObject("CUBE"),
			glm::value_ptr(model2), glm::value_ptr(view), glm::value_ptr(proj));

		draw(gallery.getShader("CAMERA"), gallery.getObject("SPHERE"),
			glm::value_ptr(model), glm::value_ptr(view), glm::value_ptr(proj));
		
	}

	gallery.term();
	window.term();

	return 0;
}