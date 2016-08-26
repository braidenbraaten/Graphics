#include "gldecs.h"
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
	for (int i = 0; i < attrib.vertices.size(); i += 3)
	{
		verts[i] = { attrib.vertices[i],
					 attrib.vertices[i+1],
					 attrib.vertices[i+2], 1};

	}


	//we are using our own vertex structure
	return Geometry();
}
