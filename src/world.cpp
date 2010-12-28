#include "world.h"
#include "globals.h"
#include "vertex.h"
#include "wall.h"
#include "bullet.h"

// This is a debugging symbol from bullet.
extern int gNumClampedCcdMotions;

World::World() {
	rotate = 0.0f;

	walls.push_back(new Wall(ph::vec3f(-10, 0, 5),
	                         ph::vec3f(-10, 10, 10),
	                         ph::vec3f(-10, 10, 0)));

	walls.push_back(new Wall(ph::vec3f(-5, 10, 5),
	                         ph::vec3f(0, 10, 10),
	                         ph::vec3f(0, 10, 0)));

	btRigidBody::btRigidBodyConstructionInfo
		construct(0, NULL, G::shapes::ground, btVector3(0, 0, 0));
	groundBody = new btRigidBody(construct);

	G::physics->addRigidBody(groundBody);

	addEntity(new Bullet(ph::vec3f(0, 2, 2), ph::vec3f(0,0,0)));
}

World::~World () {
	G::physics->removeRigidBody(groundBody);
	delete groundBody;

	for (std::vector<Wall*>::iterator it = walls.begin();
	     it != walls.end(); it++)
	{
		delete *it;
		*it = NULL;
	}

	for (std::vector<Entity*>::iterator it = entities.begin();
	     it != entities.end(); it++)
	{
		delete *it;
		*it = NULL;
	}
}

void World::update() {
	int steps = G::physics->stepSimulation(1/G::framerate, 10);
	player.update();
	rotate += 1.0f;

	printf("%d\n", gNumClampedCcdMotions);
}

void World::addEntity(Entity *ent) {
	entities.push_back(ent);
}

void World::draw() {
	GLCheck( glPushMatrix() );

	player.setupCamera();

	drawFloor();
	drawCube();

	foreach(Wall *w, walls) {
		w->draw();
	}

	if (G::debugMode) {
		GLCheck( glBindTexture(GL_TEXTURE_2D, 0) );
		GLCheck( glDepthFunc(GL_ALWAYS) );
		G::physics->debugDrawWorld();
	}

	GLCheck( glPopMatrix() );

	player.draw();
}

void World::drawFloor() {
	Vertex floor_vertices[] = {
		Vertex(-10, +10, 0, 0.5, 0.5, 0.5),
		Vertex(-10, -10, 0, 0.5, 0.5, 0.5),
		Vertex(+10, -10, 0, 0.5, 0.5, 0.5),
		Vertex(+10, +10, 0, 0.5, 0.5, 0.5),
	};

	GLCheck( glBindTexture(GL_TEXTURE_2D, 0) );

	floor_vertices->draw(GL_QUADS, 4);
}

void World::drawCube() {
	Vertex cube_vertices[] = {
		Vertex( -0.2, -0.2, +0.2, 0, 0 ),
		Vertex( -0.2, -0.2, -0.2, 0, 1 ),
		Vertex( +0.2, -0.2, -0.2, 1, 1 ),
		Vertex( +0.2, -0.2, +0.2, 1, 0 ),
		Vertex( -0.2, +0.2, +0.2, 1, 0 ),
		Vertex( -0.2, +0.2, -0.2, 1, 1 ),
		Vertex( +0.2, +0.2, -0.2, 0, 1 ),
		Vertex( +0.2, +0.2, +0.2, 0, 0 ),
	};

	unsigned short cube_faces[] = {
		0, 1, 2, 3, // front
		0, 4, 5, 1, // left
		0, 3, 7, 4, // top
		1, 5, 6, 2, // bottom
		2, 6, 7, 3, // right
		4, 7, 6, 5, // back
	};

	unsigned short cube_edges[] = {
		0,1, 1,2, 2,3, 3,0,
		4,7, 7,6, 6,5, 5,4,
		0,4, 1,5, 2,6, 3,7,
	};

	G::images::wall.Bind();

	GLCheck( glPushMatrix() );

	GLCheck( glTranslatef(0, 0.21, 5) );
	GLCheck( glRotatef(rotate, 0, 1, 0) );

	cube_vertices->drawElements(GL_QUADS, 24, GL_UNSIGNED_SHORT,
	                            cube_faces);
	
	GLCheck( glDisableClientState(GL_TEXTURE_COORD_ARRAY) );
	GLCheck( glDisableClientState(GL_COLOR_ARRAY) );
	GLCheck( glColor3f(0, 0, 0) );

	cube_vertices->justDrawElements(GL_LINES, 24, GL_UNSIGNED_SHORT,
	                                cube_edges);

	GLCheck( glPopMatrix() );
}
