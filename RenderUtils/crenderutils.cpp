#include "gldecs.h"
#include "globjects.h"
#include "Vertex.h"
#include "crenderutils.h"
#include <cstdio>

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
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	
	// index of the attribute, number of elements, type, normalized?, size of vertex, offset
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)16);

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

void makeTexture(unsigned width, unsigned height, unsigned format, const unsigned char * pixels)
{
	Texture retval = {0, width, height, format};

	glGenTextures(1, &retval.handle);			//Declaration 
	glBindTexture(GL_TEXTURE_2D, retval.handle);//Scoping


	glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, pixels);

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
	char vsource[5012]; //max of 5012 characters
	char fsource[5012]; // will change later

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

	Vertex *verts = new Vertex[attrib.vertices.size() / 3];
	unsigned * tris = new unsigned[shapes[0].mesh.indices.size()];


	

	for (int i = 0; i < attrib.vertices.size() / 3; ++i)
	{
		verts[i] = { attrib.vertices[i *3],
					 attrib.vertices[i *3+1],
					 attrib.vertices[i *3+2], 1};

		verts[i].color[0] = rand() * 1.0f / RAND_MAX;
		verts[i].color[1] = rand() * 1.0f / RAND_MAX;
		verts[i].color[2] = rand() * 1.0f / RAND_MAX;
		verts[i].color[3] = 1;
	}

	for (int i = 0; i < shapes[0].mesh.indices.size(); ++i)
	{
		tris[i] = shapes[0].mesh.indices[i].vertex_index;
	}

	Geometry retval = makeGeometry(verts, attrib.vertices.size() / 3,
												     tris, shapes[0].mesh.indices.size());

	delete[] verts;
	delete[] tris;
	//we are using our own vertex structure
	return retval;
}
