#ifndef _CFPS_H_
#define _CFPS_H_
 
/* Modified from from http://www.sfml-dev.org/wiki/en/sources/fps */

#include <SFML/System/Clock.hpp>

class FPS {
private:
	static int frame, fps;
	static sf::Clock clock;
 
public:
	static void Update();
	static int GetFPS();
};

int FPS::frame = 0;
int FPS::fps = 0;
sf::Clock FPS::clock;
 
void FPS::Update() {
	if(FPS::clock.GetElapsedTime() >= 1.f)
	{
		FPS::fps = frame;
		FPS::frame = 0;
		FPS::clock.Reset();
	}
 
	frame++;
}
 
int FPS::GetFPS() {
	return FPS::fps;
}
 
#endif
