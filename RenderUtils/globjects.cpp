#include "globjects.h"

//Vertex::Vertex()
//{
//	
//}
//
//Vertex& Vertex::operator=(const Vector4& vec)
//{
//	this->position[0] = vec.x;
//	this->position[1] = vec.y;
//	this->position[2] = vec.z;
//	this->position[3] = vec.w;
//	return *this;
//}
//
//Vertex::Vertex(const Vector4 vec)
//{
//	this-> position[0] = vec.x;
//	this-> position[1] = vec.y;
//	this-> position[2] = vec.z;
//	this-> position[3] = vec.w;
//}


Vector3::Vector3()
{
	
}

Vector3::Vector3(float a, float b, float c)
{
	this->x = a;
	this->y = b;
	this->z = c;
}


Vector4::Vector4()
{
	
}
Vector4::Vector4(float a, float b , float c, float d)
{
	this-> x = a;
	this-> y = b;
	this-> z = c;
	this-> w = d;
}

