#include "bindings.h"

void setupKeyBindings() {
	sf::Event e;

	G::keymap.attach(&G::window);

	e.Type = sf::Event::Closed;
	G::keymap.bindEvent(e, &quitGame);

	e.Type = sf::Event::KeyPressed;
	e.Key.Code = sf::Key::Escape;
	G::keymap.bindEvent(e, &quitGame);

	e.Type = sf::Event::MouseMoved;
	G::keymap.bindEvent(e, &lookAround);

	G::keymap.bindKey(sf::Key::Left, &strafeLeft);
	G::keymap.bindKey(sf::Key::Right, &strafeRight);
	G::keymap.bindKey(sf::Key::Down, &strafeBack);
	G::keymap.bindKey(sf::Key::Up, &strafeFwd);
}

void quitGame(sf::Event ev, bool real) {
	G::window.Close();
}

void lookAround(sf::Event ev, bool real) {
	sf::Vector2i v = G::getMouseMoveDelta(ev);
	if (v.x == 0 && v.y == 0)
		return;
	G::player.changeOrientationWithMouse(v.x, v.y);
}

void strafeFwd(sf::Event, bool) {
	G::player.strafe(1, 0);
}
void strafeBack(sf::Event, bool) {
	G::player.strafe(-1, 0);
}
void strafeLeft(sf::Event, bool) {
	G::player.strafe(0, -1);
}
void strafeRight(sf::Event, bool) {
	G::player.strafe(0, 1);
}
