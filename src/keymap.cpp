#include "keymap.h"

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
