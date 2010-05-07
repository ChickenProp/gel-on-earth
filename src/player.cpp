#include "player.h"

Player::Player() {
	pos = sf::Vector3f(0,0,0);
	vel = sf::Vector3f(0,0,0);
	orientation = vSpherical(1, 3, 90);
}

void Player::update() {
	pos += vel;
	vel = sf::Vector3f(0,0,0);
}

void Player::strafe(float fwd, float side) {
	sf::Vector3f front = vNormalize(vProjectXY(orientation));
	sf::Vector3f left = vCross(front, sf::Vector3f(0, 0, 1));

	vel += (front*fwd + left*side)/50.0f;
}

void Player::setupCamera() {
	gluLookAt(orientation.x, orientation.z, orientation.y,
	          0, 0, 0,
	          0, 1, 0);

	glTranslatef(-pos.x, -pos.z - 1, -pos.y);
}

sf::Vector3f Player::changeOrientationWithMouse(int x, int y) {
	orientation = vSpherical(1,
	                         clampd(vTheta(orientation)+y, -60, 60),
	                         vPhi(orientation)+x);
	return orientation;
}
