#include "includes.h"
#include "globals.h"
#include "bindings.h"
#include "fps.h"
#include "world.h"
#include "menu.h"
#include "debug-draw.h"

int main(int argc, char **argv) {
	// Build the broadphase
	btBroadphaseInterface* broadphase = new btDbvtBroadphase();
 
	// Set up the collision configuration and dispatcher
	btDefaultCollisionConfiguration* collisionConfiguration
		= new btDefaultCollisionConfiguration();
	btCollisionDispatcher* dispatcher
		= new btCollisionDispatcher(collisionConfiguration);
 
	// The actual physics solver
	btSequentialImpulseConstraintSolver* solver
		= new btSequentialImpulseConstraintSolver;
 
	// The world.
	G::physics = new btDiscreteDynamicsWorld(dispatcher, broadphase, solver,
	                                         collisionConfiguration);
	G::physics->setGravity(btVector3(0, 0, -10));

	DebugDraw *dbg = new DebugDraw();
	G::physics->setDebugDrawer(dbg);
	dbg->setDebugMode(btIDebugDraw::DBG_DrawAabb
	                  | btIDebugDraw::DBG_DrawWireframe);

	if (argc >= 2)
		G::debugMode = 1;

	G::window.Create(sf::VideoMode(G::windowWidth, G::windowHeight, 32),
	                 "Gel on Earth");
	//G::window.PreserveOpenGLStates(true);
	G::window.ShowMouseCursor(false);
	int cX = (int) G::windowCentre.x;
	int cY = (int) G::windowCentre.y;
	G::window.SetCursorPosition(cX, cY);
	G::window.SetFramerateLimit(G::framerate);

	G::gameScreen = new World();
	G::menuScreen = new Menu();
	G::curScreen = G::gameScreen;
	setupKeyBindings();

	sf::String fpsStr("", sf::Font::GetDefaultFont(), 15);
	char fpsCStr[10] = "";
	fpsStr.SetColor(sf::Color(0,0,0));

	while (G::window.IsOpened()) {
		sf::Event ev;
		while (G::window.GetEvent(ev)) {

			/* We calculate the delta-position of a MouseMove event
			   by taking its distance from the centre of the
			   screen. So it needs to have been reset there after
			   the previous event. If we ever stop doing that,
			   G::getMouseMoveDelta will stop working.

			   I don't know if this works properly. If I wiggle the
			   mouse fast, it produces a lot of events at position
			   (320, 240), which seems unlikely. It appears to work
			   well enough in practice, and if the handler ignores
			   (0, 0)-deltas, there's no problem except maybe
			   speed. Possibly the X server has trouble keeping up:
			   I should test wiggling with SDL events, for example.

			   If SFML just provided mouse delta in the event, this
			   wouldn't be necessary. :/
			*/
			if (ev.Type == sf::Event::MouseMoved) {
				int cX = (int) G::windowCentre.x;
				int cY = (int) G::windowCentre.y;
				G::window.SetCursorPosition(cX, cY);
			}

			G::curScreen->keymap.handleEvent(ev);
		}

		G::curScreen->keymap.handleNonEvents();

		// We might have closed the window in the event loop. If so,
		// trying to draw will produce an X error. (Interestingly, not
		// if PreserveOpenGLStates is on, though looking at the code
		// I can't work out why that matters.)
		if (!G::window.IsOpened())
			break;

		G::curScreen->update();

		G::window.SetActive();
		GLCheck( glClearColor(1, 1, 1, 1) );
		GLCheck( glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT) );
		GLCheck( glEnable(GL_ALPHA_TEST) );
		GLCheck( glEnable(GL_DEPTH_TEST) );
		GLCheck( glEnable(GL_BLEND) );
		GLCheck( glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA) );

		GLCheck( glMatrixMode(GL_PROJECTION) );
		GLCheck( glLoadIdentity() );
		GLCheck( gluPerspective(90., G::windowWidth/G::windowHeight,
		                        G::clipNear, G::clipFar) );

		GLCheck( glMatrixMode(GL_MODELVIEW) );
		GLCheck( glLoadIdentity() );

		GLCheck( glOrtho(-1, 1, -1, 1, G::clipNear, G::clipFar) );

		GLCheck( glDepthFunc(GL_LESS) );

		G::curScreen->draw();

		GLCheck( glDepthFunc(GL_ALWAYS) );

		FPS::Update();
		sprintf(fpsCStr, "%4d fps", FPS::GetFPS());
		fpsStr.SetText(fpsCStr);
		G::window.Draw(fpsStr);

		G::window.Display();
	}

	delete G::gameScreen;
	delete G::menuScreen;

	delete broadphase;
	delete collisionConfiguration;
	delete dispatcher;
	delete solver;
	delete G::physics;

	return 0;
}
