#ifndef GOE_WALL_H
#define GOE_WALL_H

#include "vertex.h"

class Wall {
public:
	Wall (const ph::vec3f *c);
	Vertex corners[4];

	void draw();
};

#endif
