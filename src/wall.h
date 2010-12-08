#ifndef GOE_WALL_H
#define GOE_WALL_H

#include "vertex.h"

class Wall {
public:
	Wall (const ph::vec3f centre,
	      const ph::vec3f topright,
	      const ph::vec3f botright);
	~Wall();

	Vertex corners[4];

	sf::Sprite sprite; // Just to point to an sf::Image.

	btCollisionShape* shape;
	btRigidBody* body;

	void draw();
};

#endif
