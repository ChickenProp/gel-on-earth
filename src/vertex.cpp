#include "vertex.h"
#include "includes.h"

int Vertex::stride = sizeof(Vertex);

Vertex::Vertex ()
	: hasTexture(false) {}
Vertex::Vertex (float x, float y, float z)
	: x(x), y(y), z(z),
	  hasTexture(false) {}
Vertex::Vertex (float x, float y, float z, float s, float t)
	: x(x), y(y), z(z),
	  hasTexture(true), s(s), t(t),
	  r(1), g(1), b(1), a(1) {}
Vertex::Vertex (float x, float y, float z,
                float r, float g, float b, float a)
	: x(x), y(y), z(z),
	  hasTexture(false),
	  r(r), g(g), b(b), a(a) {}
Vertex::Vertex (const ph::vec3f &v, float s, float t)
	: x(v.x), y(v.y), z(v.z),
	  hasTexture(true), s(s), t(t),
	  r(1), g(1), b(1), a(1) {}
Vertex::Vertex (const ph::vec3f &v, float r, float g, float b, float a)
	: x(v.x), y(v.y), z(v.z),
	  hasTexture(false),
	  r(r), g(g), b(b), a(a) {}

void Vertex::setupPointers() {
	GLCheck( glVertexPointer(3, GL_FLOAT, stride, &x) );
	GLCheck( glColorPointer(4, GL_FLOAT, stride, &r) );

	if (hasTexture)
		GLCheck( glTexCoordPointer(2, GL_FLOAT, stride, &s) );
}

void Vertex::setupClientState() {
	GLCheck( glEnableClientState(GL_VERTEX_ARRAY) );
	GLCheck( glEnableClientState(GL_COLOR_ARRAY) );

	if (hasTexture)
		GLCheck( glEnableClientState(GL_TEXTURE_COORD_ARRAY) );
}
