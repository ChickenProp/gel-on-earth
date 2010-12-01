#ifndef _VERTEX_H
#define _VERTEX_H

#include "includes.h"

// A vertex class that only has a position, which the others will inherit from.
class VertexSup {
public:
	// Intuitively, x and y are parallel to the ground, and z is "up".
	// OpenGL has y being "up". So I swap the position of y and z, so now
	// it works like I expect.
	float x, z, y;

	static int stride;

	VertexSup (float _x, float _y, float _z)
		: x(_x), y(_y), z(_z) {}

	virtual void setPointers();
	virtual void setClientState ();
	virtual void draw (int mode, int count);
	virtual void drawElems (int mode, int count, int type,
	                        const void *indices);
};

// The main vertex class, so it gets the shortest name.
class Vertex : public VertexSup {
public:
	float s, t;

	// Apparently a size-multiple of 32 bytes is good. Floats tend to be 4,
	// and subclassing seems to add 4.
	// http://www.opengl.org/wiki/Vertex_Formats
	float padding[2];

	static int stride;

	Vertex () : VertexSup(0, 0, 0), s(0), t(0) {}

	Vertex(float _x, float _y, float _z)
		: VertexSup(_x, _y, _z), s(0), t(0) {}

	Vertex(float _x, float _y, float _z, float _s, float _t)
		: VertexSup(_x, _y, _z), s(_s), t(_t) {}

	Vertex(ph::vec3f v, float _s, float _t)
		: VertexSup(v.x, v.y, v.z), s(_s), t(_t) {}

	void setPointers ();
	void setClientState ();
};

// The same thing, but with colours instead of texture coordinates.
// This one doesn't need padding, since it's already 32 bytes.
class VertexC : public VertexSup {
public: 
	float r, g, b, a;

	static int stride;

	VertexC () : VertexSup(0, 0, 0), r(0), g(0), b(0), a(1) {}

	VertexC (float _x, float _y, float _z)
		: VertexSup(_x, _y, _z), r(0), g(0), b(0), a(1) {}

	VertexC (float _x, float _y, float _z, float _r, float _g, float _b)
		: VertexSup(_x, _y, _z), r(_r), g(_g), b(_b), a(1) {}

	VertexC (float _x, float _y, float _z,
	        float _r, float _g, float _b, float _a)
		: VertexSup(_x, _y, _z), r(_r), g(_g), b(_b), a(_a) {}

	VertexC (ph::vec3f v, float _r, float _g, float _b)
		: VertexSup(v.x, v.y, v.z), r(_r), g(_g), b(_b), a(1) {}

	VertexC (ph::vec3f v, float _r, float _g, float _b, float _a)
		: VertexSup(v.x, v.y, v.z), r(_r), g(_g), b(_b), a(_a) {}

	void setPointers ();
	void setClientState ();
};

#endif
