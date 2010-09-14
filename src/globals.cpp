#include "globals.h"

sf::RenderWindow G::window;
int G::windowWidth = 640;
int G::windowHeight = 480;
sf::Vector2f G::windowCentre (320.0f, 240.0f);
float G::clipNear = 1.0;
float G::clipFar = 10.0;
float G::framerate = 60;

sf::Clock G::clock;

World *G::gameScreen = NULL;
Menu *G::menuScreen = NULL;
Screen *G::curScreen = NULL;

btDiscreteDynamicsWorld *G::physics = NULL;

btCollisionShape* G::Shapes::ground
	= new btStaticPlaneShape(btVector3(0, 0, 1), 0);

sf::Vector2i G::getMouseMoveDelta(sf::Event e) {
	return sf::Vector2i((int) windowCentre.x - e.MouseMove.X,
	                    (int) windowCentre.y - e.MouseMove.Y);
}
