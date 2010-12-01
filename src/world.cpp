#include "world.h"
#include "globals.h"
#include "vertex.h"
#include "wall.h"

World::World() {
	wallImage.LoadFromFile("media/wall.tga");
	rotate = 0.0f;

	walls.push_back(new Wall(ph::vec3f(-10, 0, 5),
	                         ph::vec3f(-10, 10, 10),
	                         ph::vec3f(-10, 10, 0)));

	btRigidBody::btRigidBodyConstructionInfo
		construct(0, NULL, G::Shapes::ground, btVector3(0, 0, 0));
	groundBody = new btRigidBody(construct);

	G::physics->addRigidBody(groundBody);
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
}

void World::update() {
	int steps = G::physics->stepSimulation(1/G::framerate, 10);
	player.update();
	rotate += 1.0f;
}

void World::draw() {
	VertexC floor_vertices[] = {
		VertexC(-10, +10, 0, 0.5, 0.5, 0.5),
		VertexC(-10, -10, 0, 0.5, 0.5, 0.5),
		VertexC(+10, -10, 0, 0.5, 0.5, 0.5),
		VertexC(+10, +10, 0, 0.5, 0.5, 0.5),
	};

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

	GLCheck( glPushMatrix() );

	player.setupCamera();

	GLCheck( glBindTexture(GL_TEXTURE_2D, 0) );

	floor_vertices[0].draw(GL_QUADS, 4);

	wallImage.Bind();

	GLCheck( glPushMatrix() );

	GLCheck( glTranslatef(0, 0.21, 5) );
	GLCheck( glRotatef(rotate, 0, 1, 0) );

	GLCheck( glColor3f(1, 1, 1) );
	cube_vertices[0].drawElems(GL_QUADS, 24, GL_UNSIGNED_SHORT, cube_faces);

	GLCheck( glColor3f(0, 0, 0) );
	GLCheck( glDrawElements(GL_LINES, 24, GL_UNSIGNED_SHORT, cube_edges) );

	GLCheck( glPopMatrix() );

	GLCheck( glColor3f(1, 1, 1) );
	walls[0]->draw();	

	if (G::debugMode) {
		GLCheck( glBindTexture(GL_TEXTURE_2D, 0) );
		GLCheck( glDepthFunc(GL_ALWAYS) );
		G::physics->debugDrawWorld();
	}

	GLCheck( glPopMatrix() );

	player.draw();
}
