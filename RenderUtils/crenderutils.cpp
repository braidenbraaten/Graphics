#include "gldecs.h"
#include "globjects.h"
#include "crenderutils.h"
#include <cstdio>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"





Texture loadTexture(const char * path)
{
	int w, h, f;
	unsigned char *p;
	
	Texture retval = {0,0,0,0};

	p = stbi_load(path, &w, &h, &f, STBI_default);

	if (!p) return retval;

	switch (f)
	{
	case STBI_grey		: f = GL_RED;	break;
	case STBI_grey_alpha: f = GL_RG;	break;
	case STBI_rgb       : f = GL_RGB;	break;
	case STBI_rgb_alpha : f = GL_RGBA;	break;
	}

	retval = makeTexture(w, h, f, p);
	stbi_image_free(p);
	return retval;
}
Geometry makeGeometry(const Vertex * verts, size_t vsize,const unsigned int * tris, size_t tsize)
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
	glBufferData(GL_ARRAY_BUFFER        , vsize * sizeof(Vertex)  , verts, GL_STATIC_DRAW);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, tsize * sizeof(unsigned), tris , GL_STATIC_DRAW);

	// Attributes let us tell openGL how memory is laid out
	glEnableVertexAttribArray(0); //POSITION
	glEnableVertexAttribArray(1); //COLOR
	glEnableVertexAttribArray(2); //normal
	glEnableVertexAttribArray(3); // texCoord
	
	// index of the attribute, number of elements, type, normalized?, size of vertex, offset
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)Vertex::POSITION);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)Vertex::COLOR);
	glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)Vertex::NORMAL);
	glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)Vertex::TEXCOORD);

	//unscope the variables
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER        , 0);
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
	Shader retval;

	retval.handle = glCreateProgram();
	//create our variables
	unsigned vs = glCreateShader(GL_VERTEX_SHADER);
	unsigned fs = glCreateShader(GL_FRAGMENT_SHADER);

	//init our variables
	glShaderSource(vs, 1, &vsource, NULL);
	glShaderSource(fs, 1, &fsource, NULL);
	//compile the shaders
	glCompileShader(vs);
	glCompileShader(fs);
	//link the shaders into a single program
	glAttachShader(retval.handle, vs);
	glAttachShader(retval.handle, fs);
	glLinkProgram(retval.handle);
	//no longer need these! their functionality has been eaten by the program

	// error handl
	GLint programStatus = GL_FALSE;
	glGetProgramiv(retval.handle, GL_LINK_STATUS, &programStatus);
	if (programStatus != GL_TRUE)
	{
		GLsizei log_length = 0;
		GLchar message[1024];

		glGetProgramInfoLog(retval.handle, 1024, &log_length, message);
		fprintf(stderr, "%s", message);
		assert(false && "Shader failed to link!");

	}

	glDeleteShader(vs);
	glDeleteShader(fs);

	return retval;
}



void freeShader(Shader &shader)
{
	glDeleteProgram(shader.handle);
	shader.handle = NULL;
}

void draw(const Shader &shader, const Geometry &geometry)
{
	glUseProgram(shader.handle);

	//binding the VAO also binds the IBO(tri) and VBO( verts)
	glBindVertexArray(geometry.vao);

	//Draw elements will draw the vertices that are currently bound
	//using an array of indeces.
	//IF AN IBO IS BOUND, we don't need to provide any indices.
	glDrawElements(GL_TRIANGLES, geometry.size, GL_UNSIGNED_INT, 0);

}

void draw(const Shader &shader, const Geometry &geometry, float time)
{
	glUseProgram(shader.handle);
	glBindVertexArray(geometry.vao);
	

	//    WIREFRAME MODE
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	//gets the location index number of the time variable   -1 = failed
	int loc = glGetUniformLocation(shader.handle, "time");
	//makes sure that the time passed in is set for the time var in the shader
	glUniform1f(loc, time);

	glDrawElements(GL_TRIANGLES, geometry.size, GL_UNSIGNED_INT, 0);
}

void draw(const Shader &s, const Geometry &g,
	const float M[16], const float V[16], const float P[16], float time)
{

	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST); //testing Z depth

							 //makes it WIREFRAME
							 //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glUseProgram(s.handle);
	glBindVertexArray(g.vao);

	glUniformMatrix4fv(0, 1, GL_FALSE, P);
	glUniformMatrix4fv(1, 1, GL_FALSE, V);
	glUniformMatrix4fv(2, 1, GL_FALSE, M);

	glUniform1f(3, time);


	glDrawElements(GL_TRIANGLES, g.size, GL_UNSIGNED_INT, 0);
}



	void drawPhong(const Shader &s, const Geometry &g,
	const float M[16], const float V[16], const float P[16])
{

	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST); //testing Z depth

							 //makes it WIREFRAME
							 //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glUseProgram(s.handle);
	glBindVertexArray(g.vao);

	glUniformMatrix4fv(0, 1, GL_FALSE, P);
	glUniformMatrix4fv(1, 1, GL_FALSE, V);
	glUniformMatrix4fv(2, 1, GL_FALSE, M);




	glDrawElements(GL_TRIANGLES, g.size, GL_UNSIGNED_INT, 0);
}

void draw(const Shader &s, const Geometry &g, const Texture &t,
						const float M[16], const float V[16], const float P[16], float time)
{

	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST); //testing Z depth
	
	//makes it WIREFRAME
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glUseProgram(s.handle);
	glBindVertexArray(g.vao);

	glUniformMatrix4fv(0, 1, GL_FALSE, P);
	glUniformMatrix4fv(1, 1, GL_FALSE, V);
	glUniformMatrix4fv(2, 1, GL_FALSE, M);

	glUniform1f(3, time);

	glActiveTexture(GL_TEXTURE0); // look at slot 0
	glBindTexture(GL_TEXTURE_2D, t.handle); //put it in that slot
	glUniform1i(4, 0); //second value is texture slot number 

	glDrawElements(GL_TRIANGLES, g.size, GL_UNSIGNED_INT, 0);
}

Texture makeTexture(unsigned width, unsigned height, unsigned format, const unsigned char * pixels)
{
	Texture retval = {0, width, height, format};

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

#include <string.h>
#include <fstream>
#include <istream>

std::string fileToArray(const char *path)
{
	std::ifstream infile{ path };
	std::string file_contents{ std::istreambuf_iterator<char>(infile), 
							   std::istreambuf_iterator<char>() };


	
	

	return file_contents;
}

Shader loadShader(const char *vpath, const char *fpath)
{
	//char vsource[5012]; //max of 5012 characters
	//char fsource[5012]; // will change later

	std::string vs = fileToArray(vpath);
	std::string fs = fileToArray(fpath);

	return makeShader(vs.c_str(), fs.c_str());
}

#define TINYOBJLOADER_IMPLEMENTATION // define this in only one .cc
#include"OBJ\tiny_obj_loader.h"
#include <random>

Geometry loadOBJ(const char*path)
{
	//we can use TinOBJ to load the file
	//we can extract vertex positions and face data
	//we can create an array to store that vertex data and face data
	tinyobj::attrib_t attrib;
	std::vector<tinyobj::shape_t> shapes;
	std::vector<tinyobj::material_t> materials;
	std::string err;
	bool ret = tinyobj::LoadObj(&attrib, &shapes, &materials, &err, path);

	int vsize = shapes[0].mesh.indices.size();

	Vertex *verts = new Vertex[vsize];
	unsigned * tris = new unsigned[vsize];


	

	for (int i = 0; i < vsize; ++i)
	{
		auto &ind = shapes[0].mesh.indices[i];

		const float *n = &attrib.normals  [ind.normal_index * 3];   // +1,+2,0
		const float *p = &attrib.vertices [ind.vertex_index * 3];   //+1, +2, 1
		const float *t = &attrib.texcoords[ind.texcoord_index * 2];//+1

		verts[i].position = glm::vec4(p[0],p[1],p[2],1.f);
		verts[i].normal =   glm::vec4(n[0],n[1],n[2],0.f);
		verts[i].texcoord = glm::vec2(t[0],t[1]);

		tris[i] = i; // 0-35
	}

	Geometry retval = makeGeometry(verts, vsize, tris, vsize);
	delete[] verts;
	delete[] tris;
	//we are using our own vertex structure
	return retval;
}
