#ifndef _KEYMAP_H
#define _KEYMAP_H

#include "includes.h"

typedef void handler_t(sf::Event, bool);

class Keymap {
public:
	std::map<sf::Event, handler_t> eventMap;
	std::map<sf::Key::Code, handler_t> keyMap;
	std::map<sf::Mouse::Button, handler_t> mouseMap;

	static bool compareEvents(sf::Event a, sf::Event b);
	void handleEvent(sf::Event ev, bool real);
};

#endif
