#include "includes.h"

int main()
{
	sf::Window window(sf::VideoMode(640, 480, 32), "Gel on Earth");
	window.Display();

	sf::Clock Clock;
	while (Clock.GetElapsedTime() < 5.f) {
		std::cout << Clock.GetElapsedTime() << std::endl;
		sf::Sleep(0.5f);
	}

	return 0;
}
