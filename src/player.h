#ifndef _PLAYER_H
#define _PLAYER_H

#include "includes.h"
#include "entity.h"

class Player : public Entity {
public:
	typedef Entity super;

	Player();
	~Player();

	ph::vec3f pos;
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

class PlayerMotionState : public btMotionState {
public:
	PlayerMotionState(Player *player);
	Player *player;

	void getWorldTransform(btTransform &trans) const;
	void setWorldTransform(const btTransform &trans);	
};

#endif
