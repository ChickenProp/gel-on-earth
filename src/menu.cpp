#include "menu.h"
#include "globals.h"

Menu::Menu() {
	textReturn = sf::String("Return to game", sf::Font::GetDefaultFont(), 30);
	textReturn.SetColor(sf::Color(0,0,0));
}

void Menu::draw() {
	G::window.Draw(textReturn);
}
