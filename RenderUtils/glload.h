#pragma once
#include "globjs.h"
Shader loadShader(const char *vsource, const char *fsource, bool depth = true, bool add = false, bool face = true);

Texture loadTexture(const char* path);

Geometry loadOBJ(const char*path);


