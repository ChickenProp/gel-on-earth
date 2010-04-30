#ifndef _KEYMAP_H
#define _KEYMAP_H

#include "includes.h"

typedef void (*handler_t)(sf::Event, bool);

class Keymap {
public:
	Keymap();

	std::map<sf::Event, handler_t, bool (*)(sf::Event, sf::Event)> eventMap;
	std::map<sf::Key::Code, handler_t> keyMap;
	std::map<sf::Mouse::Button, handler_t> mouseMap;

	void bind(sf::Event ev, bool real, handler_t callback);
	static bool compareEvents(sf::Event a, sf::Event b);
	void handleEvent(sf::Event ev);
};

#endif
