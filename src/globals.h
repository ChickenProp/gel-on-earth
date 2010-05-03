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

sf::RenderWindow G::window;
sf::Clock G::clock;
int G::window_width = 640;
int G::window_height = 480;
float G::clip_near = 1.0;
float G::clip_far = 10.0;
Player G::player;
Keymap G::keymap;

sf::Vector2i G::getMouseMoveDelta(sf::Event e) {
	return sf::Vector2i(window_width/2 - e.MouseMove.X,
	                    window_height/2 - e.MouseMove.Y);
}


#endif
