#pragma once
#include "glm\glm.hpp"

struct Vertex
{
	//pos = 0, color = 1, normal = 2, texcoord = 3
	glm::vec4 position; 
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

const Vertex quad_verts[4] = { { { -1,-1,0,1},{1,1,1,0},{0,0,1,0},{ 0,0   } },
							   { { 1,-1,0,1 },{1,1,0,1},{0,0,1,0},{ 1,0   } },
							   { { 1,1,0,1  },{1,0,1,1},{0,0,1,0},{ 1,1   } },
							   { { -1,1,0,1 },{0,1,1,1},{0,0,1,0},{ 0,1   } } };

const unsigned quad_tris[6] = { 0,1,2,2,3,0 };