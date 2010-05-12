#include "world.h"
#include "globals.h"

World::World() {
	wall.LoadFromFile("media/wall.tga");
	rotate = 0.0f;
}

void World::update() {
	player.update();
	rotate += 1.0f;
}

void World::draw() {
	player.setupCamera();

	glTranslatef(0, 0, 5);
	glRotatef(rotate, 0, 1, 0);
	float vertices[] = {
		-0.2, +0.2, -0.2,
		-0.2, -0.2, -0.2,
		+0.2, -0.2, -0.2,
		+0.2, +0.2, -0.2,
		-0.2, +0.2, +0.2,
		-0.2, -0.2, +0.2,
		+0.2, -0.2, +0.2,
		+0.2, +0.2, +0.2,
	};

	unsigned short texCoords[] = {
		0, 0,
		0, 1,
		1, 1,
		1, 0,
		1, 0,
		1, 1,
		0, 1,
		0, 0,
	};

	unsigned short faces[] = {
		0, 1, 2, 3, // front
		0, 4, 5, 1, // left
		0, 3, 7, 4, // top
		1, 5, 6, 2, // bottom
		2, 6, 7, 3, // right
		4, 7, 6, 5, // back
	};

	unsigned short edges[] = {
		0,1, 1,2, 2,3, 3,0,
		4,7, 7,6, 6,5, 5,4,
		0,4, 1,5, 2,6, 3,7,
	};

	wall.Bind();

	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(3, GL_FLOAT, 0, vertices);

	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glTexCoordPointer(2, GL_SHORT, 0, texCoords);

	glColor3f(1, 1, 1);
	glDrawElements(GL_QUADS, 24, GL_UNSIGNED_SHORT, faces);

	glDisableClientState(GL_TEXTURE_COORD_ARRAY);

	glBindTexture(GL_TEXTURE_2D, 0);
	glColor3f(0, 0, 0);
	glDrawElements(GL_LINES, 24, GL_UNSIGNED_SHORT, edges);

	glDisableClientState(GL_VERTEX_ARRAY);
}
