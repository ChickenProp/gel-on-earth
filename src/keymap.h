#ifndef _KEYMAP_H
#define _KEYMAP_H

#include "includes.h"

typedef void (*handler_t)(sf::Event, bool);
typedef std::map<sf::Event, handler_t, bool (*)(sf::Event, sf::Event)>
	    event_map_t;
typedef std::map<sf::Key::Code, handler_t> key_map_t;
typedef std::map<sf::Mouse::Button, handler_t> mouse_map_t;

class Keymap {
public:
	Keymap();

	event_map_t eventMap;
	key_map_t keyMap;
	mouse_map_t mouseMap;

	sf::Window *window;
	void attach(sf::Window *w);

	void bindEvent(sf::Event ev, handler_t callback);
	void bindKey(sf::Key::Code key, handler_t callback);
	void bindMouse(sf::Mouse::Button button, handler_t callback);

	static bool compareEvents(sf::Event a, sf::Event b);

	void handleEvent(sf::Event ev);
	void handleNonEvents();
};

#endif
