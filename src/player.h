#ifndef _PLAYER_H
#define _PLAYER_H

#include "includes.h"
#include "util.h"

class Player {
public:
	Player();

	sf::Vector3f pos;
	sf::Vector3f vel;
	sf::Vector3f orientation;

	void strafe(float fwd, float side);

	void setupCamera();
	sf::Vector3f changeOrientationWithMouse(int x, int y);
};

#endif
