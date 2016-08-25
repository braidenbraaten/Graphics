#include "window.h"
#include "crenderutils.h"
#include "Vertex.h"
//this is the develop branch!

int main()
{
	Window window;
	window.init();

	Vertex vert[3] = { {-.9f,-.9f, 0, 1},
					   {.4f,.6f, 0, 1},
					   {.9f,.9f, 0, 1} };

	unsigned tris[3] = {0, 1, 2};

	const char vsource[] =
						"#version 150\n"
						"in vec4 position;"
						"void main() {gl_Position = position; }";

	const char fsource[] =
							"#version 150 \n"
							"out vec4 outColor;"
							"void main() {outColor = vec4(1.0,0.0,0.0,1.0);}";

	Geometry geo = makeGeometry(vert, 3, tris, 3);
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