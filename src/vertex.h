#ifndef _VERTEX_H
#define _VERTEX_H

#include "includes.h"

class Vertex {
public:
	float x, y, z;

	bool hasTexture;
	float s, t;
	float r, g, b, a;

	/* Apparently a size-multiple of 32 bytes is good. This makes it 64. If
	   I ever start using normals, I can put those in.
	   http://www.opengl.org/wiki/Vertex_Formats */
	char padding[27];

	static int stride;

	Vertex ();
	Vertex (float x, float y, float z);
	Vertex (float x, float y, float z, float s, float t);
	Vertex (float x, float y, float z,
	        float r, float g, float b, float a=1.0f);
	Vertex (const ph::vec3f &v, float s, float t);
	Vertex (const ph::vec3f &v, float r, float g, float b, float a=1.0f);

	Vertex* setPos(float x, float y, float z);
	Vertex* setPos(const ph::vec3f &pos);
	Vertex* setTexCoords(float s, float t);
	Vertex* setHasTexture(bool h);
	Vertex* setColor(float r, float g, float b, float a=1.0f);

	void setupPointers();
	void setupClientState();

	void draw(int mode, int count);
	void drawElements(int mode, int count, int type, const void *indices);

	void justDraw(int mode, int count);
	void justDrawElements(int mode, int count, int type, const void *indices);
};

#endif
