#pragma once
#include "globjs.h"



Geometry makeGeometry(const struct Vertex *verts, size_t vsize,
	const unsigned int *tris, size_t tsize);

void freeGeometry(Geometry &);


Shader makeShader(const char *vsource, const char *fsource, bool depth = true, bool add = false, bool face = true);
void freeShader(Shader &);

//bool to switch between floats and bytes
//int for number of channels
Texture makeTexture(unsigned width, unsigned height, unsigned format, const unsigned char *pixels);
Texture makeTexture(unsigned width, unsigned height, unsigned channels, const unsigned char *pixels);

Texture makeTextureF(unsigned square, const float *pixels);
void freeTexture(Texture &t);

Framebuffer makeFramebuffer(unsigned width, unsigned height, unsigned nColors);
void FreeFramebuffer(Framebuffer &);
