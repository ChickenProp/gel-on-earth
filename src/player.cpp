#include "player.h"
#include "globals.h"

Player::Player() {
	pos = ph::vec3f(0,0,0);
	vel = ph::vec3f(0,0,0);
	orientation = ph::vec3f::spherical(1, 90, 3);

	shape = new btSphereShape(1);

	btDefaultMotionState* ms =
                new btDefaultMotionState(btTransform(btQuaternion(0,0,0,1),
		                                     btVector3(0,0,1)));

	btScalar mass = 1;
	btVector3 inertia(0, 0, 0);
	shape->calculateLocalInertia(mass, inertia);

	btRigidBody::btRigidBodyConstructionInfo
		construct(mass, ms, shape, inertia);
        body = new btRigidBody(construct);

	body->setActivationState(DISABLE_DEACTIVATION);

	G::physics->addRigidBody(body);
}

Player::~Player() {
	delete shape;
	G::physics->removeRigidBody(body);
	delete body->getMotionState();
	delete body;
}

void Player::update() {
	btTransform trans;
	body->getMotionState()->getWorldTransform(trans);
	pos.x = trans.getOrigin().getX();
	pos.y = trans.getOrigin().getY();
	pos.z = trans.getOrigin().getZ();

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

void Player::setupCamera() {
	gluLookAt(orientation.x, orientation.z, orientation.y,
	          0, 0, 0,
	          0, 1, 0);

	glTranslatef(-pos.x, -pos.z - 1, -pos.y);
}

ph::vec3f Player::changeOrientationWithMouse(int x, int y) {
	orientation = ph::vec3f::spherical(
	        1, orientation.phi()+x,
		ph::clampf(orientation.theta()+y, -60, 60) );
	
	return orientation;
	
}
