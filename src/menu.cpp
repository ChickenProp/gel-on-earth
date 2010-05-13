#include "menu.h"
#include "globals.h"

Menu::Menu() {
	textReturn = sf::String("Return to game", sf::Font::GetDefaultFont(), 30);
	textReturn.SetColor(sf::Color(0,0,0));
	textReturn.Move(G::windowCentre);
}

void Menu::draw() {
	G::gameScreen.draw();
	// Don't draw the menu behind the world.
	GLCheck( glDepthFunc(GL_ALWAYS) );
	G::window.Draw(textReturn);
}
