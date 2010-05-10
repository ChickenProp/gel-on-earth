#include "includes.h"
#include "globals.h"
#include "util.h"
#include "bindings.h"

int main()
{
	G::window.Create(sf::VideoMode(G::window_width, G::window_height, 32),
	                 "Gel on Earth");
	//G::window.PreserveOpenGLStates(true);
	G::window.ShowMouseCursor(false);
	int cX = G::window_width/2;
	int cY = G::window_height/2;
	G::window.SetCursorPosition(cX, cY);

	setupKeyBindings();

	sf::String fpsStr("", sf::Font::GetDefaultFont(), 15);
	char fpsCStr[10] = "";
	fpsStr.SetColor(sf::Color(0,0,0));

	float timeNow = 0;
	float timeLastFrame = 0;
	float dt = 0;
	int frameNum = 0;

	float timeLastFpsDisplay = 0;
	int frameLastFpsDisplay = 0;

	while (G::window.IsOpened()) {
		frameNum++;

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
				int cX = G::window_width/2;
				int cY = G::window_height/2;
				G::window.SetCursorPosition(cX, cY);
			}

			G::keymap.handleEvent(ev);
		}

		G::keymap.handleNonEvents();

		// We might have closed the window in the event loop. If so,
		// trying to draw will produce an X error. (Interestingly, not
		// if PreserveOpenGLStates is on, though looking at the code
		// I can't work out why that matters.)
		if (!G::window.IsOpened())
			break;

		G::player.update();

		G::window.SetActive();
		GLCheck( glClearColor(1, 1, 1, 1) );
		GLCheck( glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT) );
		GLCheck( glEnable(GL_ALPHA_TEST) );
		GLCheck( glEnable(GL_DEPTH_TEST) );
		GLCheck( glEnable(GL_BLEND) );
		GLCheck( glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA) );

		GLCheck( glMatrixMode(GL_PROJECTION) );
		GLCheck( glLoadIdentity() );
		GLCheck( gluPerspective(90., G::window_width/G::window_height,
		                        G::clip_near, G::clip_far) );

		GLCheck( glMatrixMode(GL_MODELVIEW) );
		GLCheck( glLoadIdentity() );

		GLCheck( glOrtho(-1, 1, -1, 1, G::clip_near, G::clip_far) );

		G::player.setupCamera();

		G::world.draw();

		timeLastFrame = timeNow;
		timeNow = G::clock.GetElapsedTime();
		dt = timeNow - timeLastFrame;

		float longdt = timeNow - timeLastFpsDisplay;
		if (longdt >= 1) {
			sprintf(fpsCStr, "%4d fps",
			        (int) ((float)(frameNum - frameLastFpsDisplay)/longdt));
			frameLastFpsDisplay = frameNum;
			timeLastFpsDisplay = timeNow;
		}
		fpsStr.SetText(fpsCStr);
		G::window.Draw(fpsStr);

		G::window.Display();
	}

	return 0;
}
