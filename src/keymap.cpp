#include "keymap.h"

Keymap::Keymap() {
	eventMap = event_map_t(Keymap::compareEvents);
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

void Keymap::bind(sf::Event ev, bool real, handler_t callback) {
	if (real)
		eventMap[ev] = callback;
	else if (ev.Type == sf::Event::KeyPressed)
		keyMap[ev.Key.Code] = callback;
	else if (ev.Type == sf::Event::MouseButtonPressed)
		mouseMap[ev.MouseButton.Button] = callback;
}

void Keymap::handleEvent(sf::Event ev) {
	event_map_t::iterator it = eventMap.find(ev);
	if (it != eventMap.end())
		((*it).second)(ev, true);
}
