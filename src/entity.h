#ifndef GOE_ENTITY_H
#define GOE_ENTITY_H

#include "includes.h"

class Entity {
public:
	Entity();
	~Entity();

	virtual void initialize(btScalar mass, btVector3 inertia,
	                        btMotionState *state);

	virtual void update();
	virtual void draw();

	btCollisionShape* shape;
	btRigidBody *body;
};

#endif

