#ifndef _WORLD_H
#define _WORLD_H

#include "includes.h"
#include "screen.h"
#include "player.h"

class World : public Screen {
public:
	World();

	Player player;

	sf::Image wall;

	void update();
	void draw();
};

#endif
