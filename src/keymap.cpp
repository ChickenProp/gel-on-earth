#include "keymap.h"

Keymap::Keymap() {
	eventMap = event_map_t(Keymap::compareEvents);
	window = NULL;
}

void Keymap::attach(sf::Window *w) {
	window = w;
}

bool Keymap::compareEvents(sf::Event a, sf::Event b) {
	if (a.Type < b.Type)
		return true;
	else if (a.Type > b.Type)
		return false;

	switch(a.Type) {
	// We don't notice modifiers for keypresses. This might not be ideal.
	case sf::Event::KeyPressed:
	case sf::Event::KeyReleased:
		return a.Key.Code < b.Key.Code;
	case sf::Event::MouseButtonPressed:
	case sf::Event::MouseButtonReleased:
		return a.MouseButton.Button < b.MouseButton.Button;
	// Don't implement joystick stuff because I can't test it.
	default:
		return false;
	}
}

void Keymap::bindEvent(sf::Event ev, handler_t callback) {
	eventMap[ev] = callback;
}
void Keymap::bindKey(sf::Key::Code key, handler_t callback) {
	keyMap[key] = callback;
}
void Keymap::bindMouse(sf::Mouse::Button button, handler_t callback) {
	mouseMap[button] = callback;
}

void Keymap::handleEvent(sf::Event ev) {
	event_map_t::iterator it = eventMap.find(ev);
	if (it != eventMap.end())
		((*it).second)(ev, true);
}

void Keymap::handleNonEvents() {
	if (!window)
		return;

	const sf::Input &input = window->GetInput();
	sf::Event e;

	e.Type = sf::Event::KeyPressed;
	key_map_t::iterator itK = keyMap.begin();
	for (; itK != keyMap.end(); itK++) {
		sf::Key::Code test = (*itK).first;
		if (! input.IsKeyDown(test))
			continue;
		e.Key.Code = test;
		((*itK).second)(e, false);
	}

	e.Type = sf::Event::MouseButtonPressed;
	mouse_map_t::iterator itM = mouseMap.begin();
	for (; itM != mouseMap.end(); itM++) {
		sf::Mouse::Button test = (*itM).first;
		if (! input.IsMouseButtonDown(test) )
			continue;
		e.MouseButton.Button = test;
		((*itM).second)(e, false);
	}
}
