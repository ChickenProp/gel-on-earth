#ifndef GOE_BULLET_H
#define GOE_BULLET_H

#include "entity.h"
#include "vertex.h"

class Bullet : public Entity {
public:
	typedef Entity super;

	Bullet(ph::vec3f pos, ph::vec3f vel);

	sf::Sprite sprite;

	Vertex localVertices[4];

	void update();
	void draw();
};

#endif
