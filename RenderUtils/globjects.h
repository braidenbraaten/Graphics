#pragma once
#include "glm\glm.hpp"
#include "glm\ext.hpp"
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

};

struct Texture
{
	unsigned handle;
	int width, height, format;

};


class VectorN
{
public:
	float x, y, z, w;

};

class Vector4 : public VectorN
{


public:
	Vector4();
	Vector4(float, float, float, float);
	

	
};

class Vector3 : public VectorN
{
public:
	Vector3();
	Vector3(float, float, float);

};



struct Vertex
{

	glm::vec4 position; // 4
	glm::vec4 color;
	glm::vec4 normal;
	glm::vec2 texcoord;
	
	enum 
	{
		POSITION = 0,
		COLOR = 16,
		NORMAL = 32,
		TEXCOORD = 48,
	};
	//Vertex();
	////init the vert position values with a vector4
	//Vertex(const Vector4 vec);
	////set vertex position values with vector4 values
	//Vertex& operator =(const Vector4& vec);
	////addop doesnt modify the object, therefore it is const


};



struct Framebuffer
{
	unsigned handle;
	unsigned width, height, nColors;
	
	Texture depth;
	Texture colors[8];

};


//void generateGrid(unsigned int rows, unsigned int cols)
//{
//	Vertex* aoVertices = new Vertex[rows * cols];
//	for (unsigned int r = 0; r < rows; ++r)
//	{
//		for (unsigned int c = 0; c < cols; ++c)
//		{
//			*aoVertices[r * cols + c].position = (float(c), 0.f, (float)r, 1.f);
//
//
//			glm::vec3 color = glm::vec3(sinf((c / (float)(cols - 1)) * (r / (float)(rows - 1))),0,0);
//		
//			//aoVertices[r * cols + c].color = {};
//		}
//	}
//	delete[] aoVertices;
//
//}

