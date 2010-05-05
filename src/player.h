#ifndef _PLAYER_H
#define _PLAYER_H

#include "includes.h"
#include "util.h"

class Player {
public:
	Player();

	sf::Vector3f pos;
	sf::Vector3f orientation;

	sf::Vector3f changeOrientationWithMouse(int x, int y);
};

#endif
