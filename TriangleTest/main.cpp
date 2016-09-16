
#include "crenderutils.h"
int main()
{
	Window window;
	window.init(1280,720);

	Framebuffer screen = {0,1280,720};

	Geometry quad = makeGeometry(quad_verts, 4, quad_tris, 6);


	Shader simple = loadShader("../res/shaders/simple.vert", "../res/shaders/simple.frag");

	while (window.step())
	{
		tdraw(simple, quad, screen);
	}

	window.term();
}