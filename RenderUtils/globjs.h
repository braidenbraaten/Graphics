#pragma once
struct Geometry
{	
	//  vbo  = Vertex Buffer Object
	//  ibo  = Index Buffer Object
	//	vao  = Vertex Array Object
    //  size = 
	unsigned vbo, ibo, vao, size;

};

struct Shader
{
	unsigned handle;
	bool depthTest;
	bool additiveBlend;
	bool faceCulling;

};

struct Texture
{
	unsigned handle;
	int width, height, format;

};


struct Framebuffer
{
	unsigned handle;
	unsigned width, height, nColors;
	
	Texture depth;
	Texture colors[8];

};




