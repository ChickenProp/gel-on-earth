#include "world.h"
#include "globals.h"
#include "vertex.h"

World::World() {
	wall.LoadFromFile("media/wall.tga");
	rotate = 0.0f;
}

void World::update() {
	player.update();
	rotate += 1.0f;
}

void World::draw() {
	float floor_vertices[] = {
		-10, 0, +10,
		-10, 0, -10,
		+10, 0, -10,
		+10, 0, +10,
	};

	Vertex cube_vertices[] = {
		Vertex( -0.2, +0.2, -0.2, 0, 0 ),
		Vertex( -0.2, -0.2, -0.2, 0, 1 ),
		Vertex( +0.2, -0.2, -0.2, 1, 1 ),
		Vertex( +0.2, +0.2, -0.2, 1, 0 ),
		Vertex( -0.2, +0.2, +0.2, 1, 0 ),
		Vertex( -0.2, -0.2, +0.2, 1, 1 ),
		Vertex( +0.2, -0.2, +0.2, 0, 1 ),
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

	player.setupCamera();

	GLCheck( glBindTexture(GL_TEXTURE_2D, 0) );
	GLCheck( glColor3f(0.5, 0.5, 0.5) );

	GLCheck( glEnableClientState(GL_VERTEX_ARRAY) );
	GLCheck( glVertexPointer(3, GL_FLOAT, 0, floor_vertices) );
	GLCheck( glDrawArrays(GL_QUADS, 0, 4) );

	wall.Bind();

	GLCheck( glTranslatef(0, 0.2, 5) );
	GLCheck( glRotatef(rotate, 0, 1, 0) );

	GLCheck( glVertexPointer(3, GL_FLOAT, cube_vertices[0].stride,
	                         &cube_vertices[0].x) );

	GLCheck( glEnableClientState(GL_TEXTURE_COORD_ARRAY) );
	GLCheck( glTexCoordPointer(2, GL_FLOAT, cube_vertices[0].stride,
	                           &cube_vertices[0].s) );

	GLCheck( glColor3f(1, 1, 1) );
	GLCheck( glDrawElements(GL_QUADS, 24, GL_UNSIGNED_SHORT, cube_faces) );

	GLCheck( glDisableClientState(GL_TEXTURE_COORD_ARRAY) );

	GLCheck( glBindTexture(GL_TEXTURE_2D, 0) );
	GLCheck( glColor3f(0, 0, 0) );
	GLCheck( glDrawElements(GL_LINES, 24, GL_UNSIGNED_SHORT, cube_edges) );

	GLCheck( glDisableClientState(GL_VERTEX_ARRAY) );
}
