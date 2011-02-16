#include "bullet.h"
#include "globals.h"
#include "world.h"

Bullet::Bullet(ph::vec3f pos, ph::vec3f vel) {
	shape = new btSphereShape(0.2);

	btScalar mass = 1;
	btMotionState *state = new btDefaultMotionState(btTransform(btQuaternion(0,0,0,1), pos));

	initialize(mass, vel, state);

	sprite.SetImage(G::images::bullet_red);

	localVertices[0] = Vertex(ph::vec3f(-1, 0, 1), 0, 1);
	localVertices[1] = Vertex(ph::vec3f(1, 0, 1), 1, 1);
	localVertices[2] = Vertex(ph::vec3f(1, 0, -1), 1, 0);
	localVertices[3] = Vertex(ph::vec3f(-1, 0, -1), 0, 0);

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

	body->setCollisionFlags(body->getCollisionFlags() |
	                        btCollisionObject::CF_NO_CONTACT_RESPONSE);
}

void Bullet::update() {
	ph::vec3f vel = body->getLinearVelocity();

	btTransform trans;
	body->getMotionState()->getWorldTransform(trans);
	ph::vec3f pos = trans.getOrigin();
}

void Bullet::draw() {
	sprite.GetImage()->Bind();

	glPushMatrix();

	btTransform trans;
	body->getMotionState()->getWorldTransform(trans);
	ph::vec3f pos = trans.getOrigin();
	ph::vec3f face = G::gameScreen->player.orientation;

	float x = pos.x; float y = pos.y; float z = pos.z;
	float fx = face.x; float fy = face.y; float fz = face.z;

	float mat[16] = { -fy, fx, 0, 0,
			  fx, fy, fz, 0,
			  fx*fz, fy*fz, -fx*fx - fy*fy, 0, // cross product
			  x, y, z, 1 };
	glMultMatrixf(mat);

	glScalef(0.2, 0.2, 0.2);

	localVertices[0].draw(GL_QUADS, 4);

	glPopMatrix();
}




