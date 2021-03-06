#ifndef _GLOBALS_H
#define _GLOBALS_H

#include "includes.h"

class Screen;
class World;
class Menu;

class G {
public:
	static sf::RenderWindow window;
	static int windowWidth;
	static int windowHeight;
	static sf::Vector2f windowCentre;
	static float clipNear;
	static float clipFar;
	static float framerate;

	/* We use this because SFML doesn't provide delta coordinates in the
	   MouseMove event. It relies on us resetting the cursor back to the
	   centre of the screen after every MouseMove event, which we do in the
	   mainloop. */
	static sf::Vector2i getMouseMoveDelta(sf::Event e);

	static sf::Clock clock;

	static World *gameScreen;
	static Menu *menuScreen;
	static Screen *curScreen;

	static bool debugMode;

	static btDiscreteDynamicsWorld *physics;

	struct shapes {
		static btCollisionShape *ground;
	};

	struct images {
		static sf::Image wall;
		static sf::Image bullet_red;
	};
	static void loadImages();

	static bool contactProcessedCallback (btManifoldPoint &cp,
	                                      void *body0, void *body1);
};

#endif
