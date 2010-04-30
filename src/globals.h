#ifndef _GLOBALS_H
#define _GLOBALS_H

#include "includes.h"

class G {
public:
	static sf::RenderWindow window;
	static sf::Clock clock;
	static int window_width;
	static int window_height;
	static float clip_near;
	static float clip_far;
};

sf::RenderWindow G::window;
sf::Clock G::clock;
int G::window_width = 640;
int G::window_height = 480;
float G::clip_near = 1.0;
float G::clip_far = 10.0;

#endif
