#ifndef _VERTEX_H
#define _VERTEX_H

class Vertex {
public:
	float x, y, z;
	float s, t;

	/* Apparently a size-multiple of 32 bytes is good. Floats tend to be 4.
	   If I ever start using normals, I can replace this with nx, ny, nz.
	   Or I can put colors in. But not both.
	   http://www.opengl.org/wiki/Vertex_Formats */
	float padding[3];

	static int stride;

Vertex()
	: x(0), y(0), z(0), s(0), t(0) {}

Vertex(float _x, float _y, float _z)
	: x(_x), y(_y), z(_z), s(0), t(0) {}

Vertex(float _x, float _y, float _z, float _s, float _t)
	: x(_x), y(_y), z(_z), s(_s), t(_t) {}
};

#endif
