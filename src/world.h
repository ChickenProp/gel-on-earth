#ifndef _WORLD_H
#define _WORLD_H

#include "includes.h"
#include "screen.h"
#include "player.h"
#include "wall.h"

class World : public Screen {
public:
	World();

	Player player;

	btRigidBody *groundBody;

	std::vector<Wall*> walls;

	//Just for the box, which I'll remove at some point.
	float rotate;
	sf::Image wallImage;

	void update();
	void draw();
};

#endif
