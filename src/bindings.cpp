#include "bindings.h"

#include "globals.h"
#include "world.h"
#include "menu.h"

void setupKeyBindings() {
	sf::Event e;

	G::gameScreen->keymap.attach(&G::window);

	e.Type = sf::Event::Closed;
	G::gameScreen->keymap.bindEvent(e, &quitGame);
	G::menuScreen->keymap.bindEvent(e, &quitGame);

	e.Type = sf::Event::KeyPressed;
	e.Key.Code = sf::Key::Escape;
	G::gameScreen->keymap.bindEvent(e, &setScreen_menu);
	G::menuScreen->keymap.bindEvent(e, &setScreen_game);

	e.Key.Code = sf::Key::Q;
	G::gameScreen->keymap.bindEvent(e, &quitGame);
	G::menuScreen->keymap.bindEvent(e, &quitGame);

	e.Type = sf::Event::MouseMoved;
	G::gameScreen->keymap.bindEvent(e, &lookAround);

	G::gameScreen->keymap.bindKey(sf::Key::Left, &strafeLeft);
	G::gameScreen->keymap.bindKey(sf::Key::Right, &strafeRight);
	G::gameScreen->keymap.bindKey(sf::Key::Down, &strafeBack);
	G::gameScreen->keymap.bindKey(sf::Key::Up, &strafeFwd);

	G::gameScreen->keymap.bindKey(sf::Key::A, &strafeLeft);
	G::gameScreen->keymap.bindKey(sf::Key::E, &strafeRight);
	G::gameScreen->keymap.bindKey(sf::Key::O, &strafeBack);
	G::gameScreen->keymap.bindKey(sf::Key::Comma, &strafeFwd);
}

void quitGame(sf::Event ev, bool real) {
	G::window.Close();
}

void lookAround(sf::Event ev, bool real) {
	sf::Vector2i v = G::getMouseMoveDelta(ev);
	if (v.x == 0 && v.y == 0)
		return;
	G::gameScreen->player.changeOrientationWithMouse(v.x, v.y);
}

void strafeFwd(sf::Event, bool) {
	G::gameScreen->player.strafe(1, 0);
}
void strafeBack(sf::Event, bool) {
	G::gameScreen->player.strafe(-1, 0);
}
void strafeLeft(sf::Event, bool) {
	G::gameScreen->player.strafe(0, -1);
}
void strafeRight(sf::Event, bool) {
	G::gameScreen->player.strafe(0, 1);
}

void setScreen_game(sf::Event, bool) {
	G::curScreen = G::gameScreen;
}
void setScreen_menu(sf::Event, bool) {
	G::curScreen = G::menuScreen;
}
