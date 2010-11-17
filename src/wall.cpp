#include "wall.h"
#include "includes.h"
#include "globals.h"

Wall::Wall(const ph::vec3f centre,
           const ph::vec3f topright,
           const ph::vec3f botright)
{
	corners[0] = Vertex(2*centre - botright, 0, 1);
	corners[1] = Vertex(2*centre - topright, 0, 0);
	corners[2] = Vertex(botright, 1, 0);
	corners[3] = Vertex(topright, 1, 1);

	float halfheight = ((topright + botright)/2).length();
	float halfwidth = ((topright + botright)/2).distance(centre);
	shape = new btBox2dShape(ph::vec3f(halfwidth, halfheight, 0));

	float mass = 0;
	btVector3 inertia;
	shape->calculateLocalInertia(mass, inertia);

	btRigidBody::btRigidBodyConstructionInfo construct
		(mass, NULL, shape, inertia);
	body = new btRigidBody(construct);

	G::physics->addRigidBody(body);
}

Wall::~Wall() {
	delete shape;
	G::physics->removeRigidBody(body);
	delete body;
}

void Wall::draw() {
	corners[0].setPointers();
	GLCheck( glDrawArrays(GL_QUADS, 0, 4) );
}           
