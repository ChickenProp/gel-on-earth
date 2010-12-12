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

void Entity::initialize (btScalar mass, btVector3 inertia, btMotionState *state)
{
	if (shape) {
		shape->calculateLocalInertia(mass, inertia);
		btRigidBody::btRigidBodyConstructionInfo
			construct(mass, state, shape, inertia);
		body = new btRigidBody(construct);

		body->setActivationState(DISABLE_DEACTIVATION);

		G::physics->addRigidBody(body);
	}
}

void Entity::update () {}
void Entity::draw () {}





