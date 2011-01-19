#include "globals.h"

sf::RenderWindow G::window;
int G::windowWidth = 640;
int G::windowHeight = 480;
sf::Vector2f G::windowCentre (320.0f, 240.0f);
float G::clipNear = 0.8;
float G::clipFar = 10.0;
float G::framerate = 60;

sf::Clock G::clock;

World *G::gameScreen = NULL;
Menu *G::menuScreen = NULL;
Screen *G::curScreen = NULL;

bool G::debugMode = 0;

btDiscreteDynamicsWorld *G::physics = NULL;

btCollisionShape* G::shapes::ground
	= new btStaticPlaneShape(btVector3(0, 0, 1), 0);

sf::Image G::images::wall;

void G::loadImages() {
	images::wall.LoadFromFile("media/wall.tga");
}

sf::Vector2i G::getMouseMoveDelta(sf::Event e) {
	return sf::Vector2i((int) windowCentre.x - e.MouseMove.X,
	                    (int) windowCentre.y - e.MouseMove.Y);
}

bool G::contactProcessedCallback (btManifoldPoint &cp, void *body0, void *body1)
{
	printf("hi\n");
	return false;
}
