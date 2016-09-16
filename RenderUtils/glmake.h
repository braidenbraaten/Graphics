#pragma once
#include "globjs.h"



Geometry makeGeometry(const struct Vertex *verts, size_t vsize,
	const unsigned int *tris, size_t tsize);

void freeGeometry(Geometry &);


Shader makeShader(const char *vsource, const char *fsource);
void freeShader(Shader &);


Texture makeTexture(unsigned width, unsigned height, unsigned format, const unsigned char *pixels);

Texture makeTextureF(unsigned square, const float *pixels);
void freeTexture(Texture &t);

Framebuffer makeFramebuffer(unsigned width, unsigned height, unsigned nColors);
void FreeFramebuffer(Framebuffer &);
