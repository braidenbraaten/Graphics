#pragma once
#include <string>
#include <map>
#include "crenderutils.h"

//Gallery is basically our asset manager, objects can go into the gallery,
//go up to a picture and look at it

//Render Object : a thing we render, i.e. Geo, mesh, polygons, etc.
//Shader Program : pipeline of shader scripts that divide and fill the screen


class Gallery
{
public:
	std::map<std::string, Geometry> objects;
	std::map<std::string, Shader>   shaders;

	bool makeShader(const char *name, const char *vsource, const char *fsource);
	bool loadShader(const char *name, const char *vpath  , const char *fpath  );

	bool makeObject(const char *name, const Vertex *verts, size_t vsize, const unsigned *tris, size_t tsize);

	bool loadObjectOBJ(const char *name, const char *path);

	const Geometry &getObject(const char *name);
	const Shader   &getShader(const char *name);

	bool init();
	bool term();
};