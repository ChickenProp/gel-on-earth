#ifndef _PLAYER_H
#define _PLAYER_H

#include "includes.h"
#include "util.h"
#include "vector.h"

class Player {
public:
	Player();

	ph::vec3f pos;
	ph::vec3f vel;
	ph::vec3f orientation;

	void strafe(float fwd, float side);

	void update();

	void setupCamera();
	ph::vec3f changeOrientationWithMouse(int x, int y);
};

#endif
