#include "player.h"
#include "globals.h"

Player::Player() {
	pos = ph::vec3f(0,0,1);
	orientation = ph::vec3f::spherical(1, 90, 3);

	shape = new btSphereShape(1);

	btMotionState* ms = new PlayerMotionState(this);

	btScalar mass = 1;
	btVector3 inertia(0, 0, 0);

	initialize(mass, inertia, ms);

	crosshairImage.LoadFromFile("media/crosshair.tga");

	crosshair.SetImage(crosshairImage);
	crosshair.Move(G::windowCentre);
}

Player::~Player() {
}

void Player::update() {
	applyFriction();
}

void Player::applyFriction() {
	ph::vec3f v = body->getLinearVelocity();
	v.z = 0;
	body->applyCentralImpulse(-v/10);
}

void Player::strafe(float fwd, float side) {
	ph::vec3f front = orientation.projectXY().normalize();
	ph::vec3f left = front.cross(ph::vec3f(0,0,1));

	body->applyCentralImpulse(front*fwd + left*side);
}

void Player::draw() {
	GLCheck( glDisable(GL_DEPTH_TEST) );
	G::window.Draw(crosshair);
	GLCheck( glEnable(GL_DEPTH_TEST) );
}

void Player::setupCamera() {
	gluLookAt(orientation.x, orientation.z, orientation.y,
	          0, 0, 0,
	          0, 1, 0);

	glTranslatef(-pos.x, -pos.z, -pos.y);
}

ph::vec3f Player::changeOrientationWithMouse(int x, int y) {
	orientation = ph::vec3f::spherical(
	        1, orientation.phi()+x,
		ph::clampf(orientation.theta()+y, -60, 60) );
	
	return orientation;	
}

PlayerMotionState::PlayerMotionState(Player *p) {
	player = p;
}

void PlayerMotionState::getWorldTransform(btTransform &trans) const {
	trans = btTransform(btQuaternion(0,0,0,1), player->pos);
}
void PlayerMotionState::setWorldTransform(const btTransform &trans) {
	player->pos = trans.getOrigin();
}
