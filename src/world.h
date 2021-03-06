#ifndef _WORLD_H
#define _WORLD_H

#include "includes.h"
#include "screen.h"
#include "player.h"

class Wall;

class World : public Screen {
public:
	World();
	~World();

	Player player;

	btRigidBody *groundBody;

	std::vector<Wall*> walls;
	std::vector<Entity*> entities;
	void addEntity(Entity *ent);
	void delEntity(Entity *ent);

	//Just for the box, which I'll remove at some point.
	float rotate;

	void update();
	void draw();
	void drawFloor();
	void drawCube();
};

#endif
