#include "entity.h"
#include "globals.h"

Entity::Entity ()
	: shape(NULL), body(NULL)
{}

Entity::~Entity() {
	if (shape)
		delete shape;

	if (body) {
		G::physics->removeRigidBody(body);

		if (body->getMotionState())
			delete body->getMotionState();

		delete body;
	}
}

void Entity::initialize (btScalar mass, btVector3 vel, btMotionState *state)
{
	if (shape) {
		btVector3 inertia;
		shape->calculateLocalInertia(mass, inertia);
		btRigidBody::btRigidBodyConstructionInfo
			construct(mass, state, shape, inertia);
		body = new btRigidBody(construct);

		body->setLinearVelocity(vel);
		body->setActivationState(DISABLE_DEACTIVATION);

		G::physics->addRigidBody(body);

		body->setUserPointer(this);
	}
}

void Entity::update () {}
void Entity::draw () {}





