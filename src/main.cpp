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

		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		gluPerspective(90., 640./480., 1., 10.);

		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		glOrtho(-1, 1, -1, 1, 1, 10);

		glColor3f(0, 0, 0);
		glBegin(GL_POINTS);
		glVertex3d(0, 0, 1.5);
		glEnd();

		window.Display();
		std::cout << clock.GetElapsedTime() << std::endl;
		sf::Sleep(0.5f);
	}

	return 0;
}
