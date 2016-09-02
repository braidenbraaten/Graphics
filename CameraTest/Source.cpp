#include "crenderutils.h"
#include "window.h"
#include "Gallery.h"
#include "Timer.h"
#include "Input.h"


#include "Camera.h"

#include "glm\glm.hpp"
#include "glm\ext.hpp"


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

	//Vertex verts[] = { { 1,1,0,1 },{ 1,-1,0,1 },{ -1,-1,0,1 },{ -1,1,0,1 } };

	//unsigned tris[6] = { 0, 5, 2,   1, 4, 5 };

	glm::mat4 proj, view, model, model2, model3;
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

		draw(gallery.getShader("CAMERA"), gallery.getObject("CUBE"), 
			glm::value_ptr(model), glm::value_ptr(view), glm::value_ptr(proj),ct );

		draw(gallery.getShader("CAMERA"), gallery.getObject("CUBE"),
			glm::value_ptr(model2), glm::value_ptr(view), glm::value_ptr(proj),ct);

		draw(gallery.getShader("CAMERA"), gallery.getObject("SPHERE"),
			glm::value_ptr(model3), glm::value_ptr(view), glm::value_ptr(proj),ct);
		
	}

	//terminate when done
	input.term();
	time.term();
	gallery.term();
	window.term();

	return 0;
}