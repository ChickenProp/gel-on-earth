#include "bullet.h"

Bullet::Bullet(ph::vec3f pos, ph::vec3f vel) {
	shape = new btSphereShape(0.2);

	btScalar mass = 1;
	btVector3 inertia = vel;
	btMotionState *state = new btDefaultMotionState(btTransform(btQuaternion(0,0,0,1), pos));

	initialize(mass, inertia, state);

	body->setGravity(btVector3(0,0,0));
	body->setCcdMotionThreshold(0.2);
	body->setCcdSweptSphereRadius(0.2);
}







