#include "menu.h"
#include "globals.h"

Menu::Menu() {
	textReturn = sf::String("Return to game", sf::Font::GetDefaultFont(), 30);
	textReturn.SetColor(sf::Color(0,0,0));
	textReturn.Move(G::window_width/2, G::window_height/2);
}

void Menu::draw() {
	G::gameScreen.draw();
	G::window.Draw(textReturn);
}
