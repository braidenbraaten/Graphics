#pragma once



struct Geometry
{
	// Vertex Buffer Object : an array of vertices
	// Index Buffer Object  : an array of indices (triangles)
	// Vertex Array Object  : Groups of two with some formatting
	// size                 : number of triangles
	unsigned vbo, ibo, vao, size;


};



Geometry makeGeometry(const struct Vertex *verts, size_t vsize, 
		                const unsigned int *tris, size_t tsize);

void freeGeometry(Geometry &);

Geometry loadOBJ(const char*path);

struct Shader
{
	unsigned handle;

};


//shader program (is a pipeline of shaders)
//vertex shader (once per vertex)
//fragment shader (once per pixel)

Shader makeShader(const char *vsource, const char *fsource);

Shader loadShader(const char *vpath, const char *fpath);

void freeShader(Shader &);

void draw(const Shader &, const Geometry &);
