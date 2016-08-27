#include "window.h"
#include "crenderutils.h"
#include "Vertex.h"
#include "Gallery.h"
//this is the develop branch!

int main()
{
	Window window;
	Gallery gallery;

	window.init(600,600);
	gallery.init();
	//clipping space coordinates
	// -1,1
	// 1920 x 1080
	Vertex vert[6] = { {.5f,0.0f, 0, 1, 1,0,0,1},
					   {-.5f,.6f, 0, 1, 0,1,0,1},
					   { .9f,.9f, 0, 1, 0,0,1,1},

					   {0.9f,0.1f,0, 1,0,1,0,1},
					   { .2f, .1f,0, 1,1,0,0,1},
					   {-.4f,0.3f,0, 1,1,1,1,1} };

	unsigned tris[6] = {0, 5, 2,   1, 4, 5};
	Geometry geo = makeGeometry(vert, 6, tris, 6);
	float time = 0;

	while (window.step())
	{
		time += 0.01667f;
		//draw(gallery.getShader("SIMPLE"), gallery.getObject("CUBE"), time);
		draw(gallery.getShader("SIMPLE"), gallery.getObject("SPHERE"),time);
		draw(gallery.getShader("SIMPLE"), geo);
	}

	gallery.term();
	window.term();

	return 0;
}