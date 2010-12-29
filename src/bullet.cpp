#include "bullet.h"

Bullet::Bullet(ph::vec3f pos, ph::vec3f vel) {
	shape = new btSphereShape(0.2);

	btScalar mass = 1;
	btVector3 inertia = vel;
	btMotionState *state = new btDefaultMotionState(btTransform(btQuaternion(0,0,0,1), pos));

	initialize(mass, inertia, state);

	body->setGravity(btVector3(0,0,0));

	// If we move further than this in a given timestep, use continuous
	// collision detection.
	body->setCcdMotionThreshold(0.2);

	// CCD sweeps a sphere along the path the body will take, then checks
	// whether it collides with anything. This is the radius of that sphere.
	// If it's too big, the bullet can get stuck in walls. I assume this
	// happens because the bullet is stopped before the sweep-sphere
	// collides, hence the bullet itself is not at that point colliding, so
	// no collision resolution happens. I don't understand why .15 would be
	// too big, given that the actual collision shape has a radius of .2,
	// but when I tried this at .15, they did sometimes get stuck.
	body->setCcdSweptSphereRadius(0.1);
}

void Bullet::update() {
	ph::vec3f vel = body->getLinearVelocity();
	printf("%f, %f, %f\n", vel.x, vel.y, vel.z);

	btTransform trans;
	body->getMotionState()->getWorldTransform(trans);
	ph::vec3f pos = trans.getOrigin();
	printf("%f, %f, %f\n", pos.x, pos.y, pos.z);
}






