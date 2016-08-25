#pragma once



struct Geometry
{
	unsigned vbo, ibo, vao, size;
	// Vertex Buffer Object : an array of vertices
	// Index Buffer Object  : an array of indices (triangles)
	// Vertex Array Object  : Groups of two with some formatting
	// size                 : number of triangles

};

Geometry makeGeometry(struct Vertex *verts, size_t vsize, 
		                unsigned int *tris, size_t tsize);

void freeGeometry(Geometry &);