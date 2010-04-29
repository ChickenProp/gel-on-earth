#include "includes.h"

int main()
{
	sf::RenderWindow window(sf::VideoMode(640, 480, 32), "Gel on Earth");
	sf::Clock clock;
       
	while (window.IsOpened()) {
		sf::Event ev;
		while (window.GetEvent(ev)) {
			if (ev.Type == sf::Event::Closed)
				window.Close();
		}

		window.Clear(sf::Color(255,255,255));
		window.Display();
		std::cout << clock.GetElapsedTime() << std::endl;
		sf::Sleep(0.5f);
	}

	return 0;
}
