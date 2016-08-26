#include "window.h"
#include "crenderutils.h"
#include "Vertex.h"
//this is the develop branch!

int main()
{
	Window window;
	window.init();

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

	const char vsource[] =
						"#version 330\n"
						"layout(location = 0)in vec4 position;"
						"layout(location = 1)in vec4 color;"
						"out vec4 vColor;"
						"void main() {vColor = color; gl_Position = position; }";

	const char fsource[] =
							"#version 150 \n"
							"in vec4 vColor;"
							"out vec4 outColor;"
							"void main() {outColor = vColor;}";

	Geometry geo = makeGeometry(vert, 6, tris, 6);
	Shader shader = makeShader(vsource, fsource);

	while (window.step())
	{
		draw(shader, geo);
	}

	freeGeometry(geo);
	freeShader(shader);
	window.term();

	return 0;
}