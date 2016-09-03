#pragma once

struct Vertex 
{
	float position[4];
	float color[4];



};

//void setVertPos(Vertex &v,float a, float b, float c, float d)
//{
//	v.position[0] = a;
//	v.position[1] = b;
//	v.position[2] = c;
//	v.position[3] = d;
//}

bool vertToVec4(Vertex &vert, Vector4 &vec)
{
	vert.position[0] = vec.x;
	vert.position[1] = vec.y;
	vert.position[2] = vec.z;
	vert.position[3] = vec.w;
}

