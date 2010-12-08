#include "wall.h"
#include "includes.h"
#include "globals.h"

Wall::Wall(const ph::vec3f centre,
           const ph::vec3f topright,
           const ph::vec3f botright)
{
	ph::vec3f topleft = centre + (centre - botright);
	ph::vec3f botleft = centre + (centre - topright);

	corners[0] = Vertex(topleft, 0, 1);
	corners[1] = Vertex(botleft, 0, 0);
	corners[2] = Vertex(botright, 1, 0);
	corners[3] = Vertex(topright, 1, 1);

	// The collision box is originally placed around the origin (axis
	// aligned in the xy-plane), so we construct a btTransform to put it
	// where it should be.

	ph::vec3f sidemid = (topright + botright)/2;
	ph::vec3f topmid = (topleft + topright)/2;

	float halfheight = topmid.distance(centre);
	float halfwidth = sidemid.distance(centre);

	ph::vec3f xtrans = (sidemid-centre).normalize();
	ph::vec3f ytrans = (topmid-centre).normalize();
	ph::vec3f ztrans = xtrans.cross(ytrans);
	btMatrix3x3 rotation (xtrans.x, ytrans.x, ztrans.x,
	                      xtrans.y, ytrans.y, ztrans.y,
	                      xtrans.z, ytrans.z, ztrans.z);
	btTransform transform(rotation, (btVector3)centre);

	shape = new btBox2dShape(ph::vec3f(halfwidth, halfheight, 0));

	float mass = 0;
	btVector3 inertia;
	shape->calculateLocalInertia(mass, inertia);

	btRigidBody::btRigidBodyConstructionInfo construct
		(mass, NULL, shape, inertia); // NULL means no motionstate.
	body = new btRigidBody(construct);
	body->setWorldTransform(transform);

	G::physics->addRigidBody(body);
}

Wall::~Wall() {
	delete shape;
	G::physics->removeRigidBody(body);
	delete body;
}

void Wall::draw() {
	corners[0].draw(GL_QUADS, 4);
}           
