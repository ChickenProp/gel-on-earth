#ifndef _VERTEX_H
#define _VERTEX_H

#include "includes.h"

class Vertex {
public:
	// Intuitively, x and y are parallel to the ground, and z is "up".
	// OpenGL has y being "up". So I swap the position of y and z, so now
	// it works like I expect.
	float x, z, y;

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
};

#endif
