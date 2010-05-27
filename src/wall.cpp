#include "wall.h"
#include "includes.h"

Wall::Wall(const ph::vec3f *v) {
	corners[0] = Vertex(v[0], 0, 1);
	corners[1] = Vertex(v[1], 0, 0);
	corners[2] = Vertex(v[2], 1, 0);
	corners[3] = Vertex(v[3], 1, 1);
}

void Wall::draw() {
	corners[0].setPointers();
	GLCheck( glDrawArrays(GL_QUADS, 0, 4) );
}           
