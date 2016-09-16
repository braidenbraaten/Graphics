#include "gldecs.h"
#include "glmake.h"
#include "Vertex.h"
//include the vertex header

Geometry makeGeometry(const Vertex * verts, size_t vsize, const unsigned int * tris, size_t tsize)
{
	Geometry retval;
	retval.size = tsize;
	//define the variables
	glGenBuffers(1, &retval.vbo); //store my vertices
	glGenBuffers(1, &retval.ibo); //store my indices
	glGenVertexArrays(1, &retval.vao); //store attribute information

									   // scope the variables
	glBindVertexArray(retval.vao);
	glBindBuffer(GL_ARRAY_BUFFER, retval.vbo); //scope our vertices
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, retval.ibo); // triangle is scoped

													   //initialize the variables
	glBufferData(GL_ARRAY_BUFFER, vsize * sizeof(Vertex), verts, GL_STATIC_DRAW);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, tsize * sizeof(unsigned), tris, GL_STATIC_DRAW);

	// Attributes let us tell openGL how memory is laid out
	glEnableVertexAttribArray(0); //POSITION
	glEnableVertexAttribArray(1); //COLOR
	glEnableVertexAttribArray(2); //normal
	glEnableVertexAttribArray(3); // texCoord

								  // index of the attribute, number of elements, type, normalized?, size of vertex, offset
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)Vertex::POSITION);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)Vertex::COLOR);
	glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)Vertex::NORMAL);
	glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)Vertex::TEXCOORD);

	//unscope the variables
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	return retval;
}

void freeGeometry(Geometry &geo)
{
	glDeleteBuffers(1, &geo.vbo);
	glDeleteBuffers(1, &geo.ibo);
	glDeleteVertexArrays(1, &geo.vao);
	geo = { 0,0,0,0 };
}

Shader makeShader(const char * vsource, const char * fsource)
{
	glog("TODO", "Find a way to implement state management.");
	// alpha blending for transparency
	//depth testing 
	//face culling
	//



	Shader retval;

	retval.handle = glCreateProgram();
	//create our variables
	unsigned vs = glCreateShader(GL_VERTEX_SHADER);
	unsigned fs = glCreateShader(GL_FRAGMENT_SHADER);

	//init our variables
	glShaderSource(vs, 1, &vsource, NULL);
	glShaderSource(fs, 1, &fsource, NULL);
	//compile the shaders
	glog_glCompileShader(vs);
	glog_glCompileShader(fs);
	//link the shaders into a single program
	glAttachShader(retval.handle, vs);
	glAttachShader(retval.handle, fs);
	glog_glLinkProgram(retval.handle);
	//no longer need these! their functionality has been eaten by the program

	// error handl
	//GLint programStatus = GL_FALSE;
	//glGetProgramiv(retval.handle, GL_LINK_STATUS, &programStatus);
	//if (programStatus != GL_TRUE)
	//{
	//	GLsizei log_length = 0;
	//	GLchar message[1024];

	//	glGetProgramInfoLog(retval.handle, 1024, &log_length, message);
	//	fprintf(stderr, "%s", message);
	//	assert(false && "Shader failed to link!");

	//}

	glDeleteShader(vs);
	glDeleteShader(fs);

	return retval;
}


void freeShader(Shader &shader)
{
	glDeleteProgram(shader.handle);
	shader.handle = NULL;
}

Texture makeTexture(unsigned width, unsigned height, unsigned format, const unsigned char * pixels)
{
	glog("TODO", "Add parameter for channel count.");
	glog("TODO", "Parameter for bit-depth?");

	Texture retval = { 0, width, height, format };

	glGenTextures(1, &retval.handle);			//Declaration 
	glBindTexture(GL_TEXTURE_2D, retval.handle);//Scoping

												//							 Mem layout                 number of channels
	glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, pixels);
	//Texture Parameter Input 
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	//unscope texture
	glBindTexture(GL_TEXTURE_2D, 0);

	return retval;

}

Texture makeTextureF(unsigned square, const float * pixels)
{
	Texture retval = { 0, square, square, GL_RED };

	glGenTextures(1, &retval.handle);			//Declaration 
	glBindTexture(GL_TEXTURE_2D, retval.handle);//Scoping

												//							 Mem layout                 number of channels
	glTexImage2D(GL_TEXTURE_2D, 0, GL_R32F, square, square, 0, GL_RED, GL_UNSIGNED_BYTE, pixels);
	//Texture Parameter Input 
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

	//unscope texture
	glBindTexture(GL_TEXTURE_2D, 0);

	return retval;
}




void freeTexture(Texture &t)
{
	glDeleteTextures(1, &t.handle);
	t = { 0,0,0,0 };
}

Framebuffer makeFramebuffer(unsigned width, unsigned height, unsigned nColors)
{
	glog("TODO", "Find a way to implement state management.");
	glog("TODO", "Better implementation of the depth buffer.");

	Framebuffer retval = { 0,width,height,nColors };

	glGenFramebuffers(1, &retval.handle);
	glBindFramebuffer(GL_FRAMEBUFFER, retval.handle);

	// DEPTH TESTING
	//////////////////////////////////////////////////////////////////////////////////
	retval.depth = makeTexture(width, height, GL_DEPTH_COMPONENT, 0);
	glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, retval.depth.handle, 0);
	//////////////////////////////////////////////////////////////////////////////////
	const GLenum attachments[8] =
	{
		GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1, GL_COLOR_ATTACHMENT2,
		GL_COLOR_ATTACHMENT3,GL_COLOR_ATTACHMENT4,GL_COLOR_ATTACHMENT5,
		GL_COLOR_ATTACHMENT6,GL_COLOR_ATTACHMENT7 };

	for (int i = 0; i < nColors && i < 8; ++i)
	{
		retval.colors[i] = makeTexture(width, height, GL_RGBA, 0);
		glFramebufferTexture(GL_FRAMEBUFFER, attachments[i], retval.colors[i].handle, 0);
	}

	glDrawBuffers(nColors, attachments);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	return retval;
}

void FreeFramebuffer(Framebuffer &fb)
{
	for (unsigned i = 0; i < fb.nColors; ++i)
	{
		freeTexture(fb.colors[i]);

		glDeleteFramebuffers(1, &fb.handle);
		fb = { 0,0,0,0 };
	}
}