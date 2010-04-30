#include "includes.h"

int main()
{
	sf::RenderWindow window(sf::VideoMode(640, 480, 32), "Gel on Earth");
	sf::Clock clock;
       
	while (window.IsOpened()) {
		sf::Event ev;
		while (window.GetEvent(ev)) {
			if (ev.Type == sf::Event::Closed)
				window.Close();
		}

		window.SetActive();
		GLCheck(glClearColor(1, 1, 1, 1));
		GLCheck(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
		GLCheck(glEnable(GL_DEPTH_TEST));

		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		gluPerspective(90., 640./480., 1., 10.);

		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		glOrtho(-1, 1, -1, 1, 1, 10);

		glTranslatef(0, 0, 5);
		glRotatef(30*clock.GetElapsedTime(), 0, 1, 0);
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
			
		glEnableClientState(GL_VERTEX_ARRAY);
		glVertexPointer(3, GL_FLOAT, 0, vertices);

		glColor3f(0, 0, 0);
		glDrawElements(GL_QUADS, 24, GL_UNSIGNED_SHORT, faces);

		glColor3f(1, 0, 0);
		glDrawElements(GL_LINES, 24, GL_UNSIGNED_SHORT, edges);

		glDisableClientState(GL_VERTEX_ARRAY);

		window.Display();
	}

	return 0;
}
