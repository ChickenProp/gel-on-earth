#ifndef _GLOBALS_H
#define _GLOBALS_H

#include "includes.h"
#include "player.h"
#include "keymap.h"

class G {
public:
	static sf::RenderWindow window;
	static int window_width;
	static int window_height;
	static float clip_near;
	static float clip_far;

	/* We use this because SFML doesn't provide delta coordinates in the
	   MouseMove event. It relies on us resetting the cursor back to the
	   centre of the screen after every MouseMove event, which we do in the
	   mainloop. */
	static sf::Vector2i getMouseMoveDelta(sf::Event e);

	static sf::Clock clock;

	static Player player;

	static Keymap keymap;
};

#endif
