#include "vertex.h"
#include "includes.h"

int VertexSup::stride = sizeof(VertexSup);
int Vertex::stride = sizeof(Vertex);
int VertexC::stride = sizeof(VertexC);

void VertexSup::setPointers () {
	GLCheck( glVertexPointer(3, GL_FLOAT, stride, &x) );
}

void VertexSup::setClientState () {
	GLCheck( glEnableClientState(GL_VERTEX_ARRAY) );
}

void VertexSup::draw (int mode, int count) {
	setPointers();
	setClientState();
	GLCheck( glDrawArrays(mode, 0, count) );
}

void VertexSup::drawElems (int mode, int count, int type, const void *indices) {
	setPointers();
	setClientState();

	GLCheck( glDrawElements(mode, count, type, indices) );
}

void Vertex::setClientState() {
	VertexSup::setClientState();

	GLCheck( glDisableClientState(GL_COLOR_ARRAY) );
	GLCheck( glEnableClientState(GL_TEXTURE_COORD_ARRAY) );
}

void Vertex::setPointers() {
	VertexSup::setPointers();

	GLCheck( glVertexPointer(3, GL_FLOAT, stride, &x) );
	GLCheck( glTexCoordPointer(2, GL_FLOAT, stride, &s) );
}

void VertexC::setClientState() {
	VertexSup::setClientState();

	GLCheck( glEnableClientState(GL_COLOR_ARRAY) );
	GLCheck( glDisableClientState(GL_TEXTURE_COORD_ARRAY) );
}

void VertexC::setPointers() {
	VertexSup::setPointers();

	GLCheck( glVertexPointer(3, GL_FLOAT, stride, &x) );
	GLCheck( glColorPointer(4, GL_FLOAT, stride, &r) );
}
