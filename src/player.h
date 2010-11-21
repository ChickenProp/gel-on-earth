#ifndef _PLAYER_H
#define _PLAYER_H

#include "includes.h"

class Player {
public:
	Player();
	~Player();

	btCollisionShape* shape;
	btRigidBody* body;

	ph::vec3f pos;
	ph::vec3f vel;
	ph::vec3f orientation;

	void strafe(float fwd, float side);

	void update();

	void applyFriction();

	sf::Image crosshairImage;
	sf::Sprite crosshair;
	void draw();
	void setupCamera();
	ph::vec3f changeOrientationWithMouse(int x, int y);
};

#endif
