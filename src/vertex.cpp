#include "vertex.h"
#include "includes.h"

int Vertex::stride = sizeof(Vertex);

void Vertex::setPointers() {
	GLCheck( glVertexPointer(3, GL_FLOAT, stride, &x) );
	GLCheck( glTexCoordPointer(2, GL_FLOAT, stride, &s) );
}

