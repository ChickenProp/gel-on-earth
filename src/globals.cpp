#include "globals.h"

sf::RenderWindow G::window;
sf::Clock G::clock;
int G::window_width = 640;
int G::window_height = 480;
float G::clip_near = 1.0;
float G::clip_far = 10.0;

World G::gameScreen;
Screen *G::curScreen = NULL;

sf::Vector2i G::getMouseMoveDelta(sf::Event e) {
	return sf::Vector2i(window_width/2 - e.MouseMove.X,
	                    window_height/2 - e.MouseMove.Y);
}
