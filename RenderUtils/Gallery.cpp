#include "Gallery.h"

bool Gallery::makeShader(const char * name, const char * vsource, const char * fsource)
{
	if (!shaders.count(std::string(name)))
	{
		shaders[name] = ::makeShader(vsource, fsource);
		return true;
	}
	else
	{
		//fprintf()
	}

}

bool Gallery::loadShader(const char * name, const char * vpath, const char * fpath)
{

		shaders[name] = ::loadShader(vpath, fpath);
		return true;
}

bool Gallery::makeObject(const char * name, const Vertex * verts, size_t vsize, const unsigned * tris, size_t tsize)
{
	objects[name] = ::makeGeometry(verts, vsize, tris, tsize);

	return false;
}

bool Gallery::loadObjectOBJ(const char * name, const char * path)
{
	objects[name] = ::loadOBJ(path);
	return true;
}

const Geometry & Gallery::getObject(const char * name)
{

	// TODO: insert return statement here
	return objects[name];
}

const Shader & Gallery::getShader(const char * name)
{
	// TODO: insert return statement here
	return shaders[name];
}

bool Gallery::init()
{
	this->loadObjectOBJ("SPHERE", "../res/models/sphere.obj");
	this->loadObjectOBJ("CUBE","../res/models/cube.obj");
	this->loadShader("SIMPLE","../res/shaders/simpleVert.txt",
								"../res/shaders/simpleFrag.txt");

	return true;
}

bool Gallery::term()
{
	//loop through my maps and call my free functions
	for each(auto shader in shaders) { freeShader  (shader.second);}
	for each(auto object in objects) { freeGeometry(object.second);}
	return false;
}
