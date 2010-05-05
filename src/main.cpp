#include "includes.h"
#include "globals.h"
#include "util.h"

void closeWindow(sf::Event ev, bool real) {
	G::window.Close();
}

void lookAround(sf::Event ev, bool real) {
	sf::Vector2i v = G::getMouseMoveDelta(ev);
	if (v.x == 0 && v.y == 0)
		return;
	G::player.changeOrientationWithMouse(v.x, v.y);
}

int main()
{
	G::window.Create(sf::VideoMode(G::window_width, G::window_height, 32),
	                 "Gel on Earth");
	G::window.ShowMouseCursor(false);
	int cX = G::window_width/2;
	int cY = G::window_height/2;
	G::window.SetCursorPosition(cX, cY);

	sf::Event e;

	G::keymap.attach(&G::window);

	e.Type = sf::Event::Closed;
	G::keymap.bindEvent(e, &closeWindow);

	e.Type = sf::Event::KeyPressed;
	e.Key.Code = sf::Key::Escape;
	G::keymap.bindEvent(e, &closeWindow);

	e.Type = sf::Event::MouseMoved;
	G::keymap.bindEvent(e, &lookAround);

	G::keymap.bindKey(sf::Key::A, &closeWindow);
	G::keymap.bindMouse(sf::Mouse::Left, &closeWindow);

	while (G::window.IsOpened()) {
		sf::Event ev;
		while (G::window.GetEvent(ev)) {

			/* We calculate the delta-position of a MouseMove event
			   by taking its distance from the centre of the
			   screen. So it needs to have been reset there after
			   the previous event. If we ever stop doing that,
			   G::getMouseMoveDelta will stop working.

			   I don't know if this works properly. If I wiggle the
			   mouse fast, it produces a lot of events at position
			   (320, 240), which seems unlikely. It appears to work
			   well enough in practice, and if the handler ignores
			   (0, 0)-deltas, there's no problem except maybe
			   speed. Possibly the X server has trouble keeping up:
			   I should test wiggling with SDL events, for example.

			   If SFML just provided mouse delta in the event, this
			   wouldn't be necessary. :/
			*/
			if (ev.Type == sf::Event::MouseMoved) {
				int cX = G::window_width/2;
				int cY = G::window_height/2;
				G::window.SetCursorPosition(cX, cY);
			}

			G::keymap.handleEvent(ev);
			if (ev.Type == sf::Event::KeyPressed) {
				switch (ev.Key.Code) {
				case sf::Key::Left:
					G::player.strafe(0, -1);
					break;
				case sf::Key::Right:
					G::player.strafe(0, 1);
					break;
				case sf::Key::Up:
					G::player.strafe(1, 0);
					break;
				case sf::Key::Down:
					G::player.strafe(-1, 0);
					break;
				}
			}

		}

		G::keymap.handleNonEvents();

		G::window.SetActive();
		GLCheck(glClearColor(1, 1, 1, 1));
		GLCheck(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
		GLCheck(glEnable(GL_DEPTH_TEST));

		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		gluPerspective(90., G::window_width/G::window_height,
		               G::clip_near, G::clip_far);

		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		glOrtho(-1, 1, -1, 1, G::clip_near, G::clip_far);

		G::player.setupCamera();

		glTranslatef(0, 0, 5);
		glRotatef(30*G::clock.GetElapsedTime(), 0, 1, 0);
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

		G::window.Display();
	}

	return 0;
}
