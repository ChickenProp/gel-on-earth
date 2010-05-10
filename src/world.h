#ifndef _WORLD_H
#define _WORLD_H

#include "includes.h"
#include "screen.h"

class World : public Screen {
public:
	World();

	sf::Image wall;

	void draw();
};

#endif
