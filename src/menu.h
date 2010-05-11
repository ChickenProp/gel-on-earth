#ifndef _MENU_H
#define _MENU_H

#include "includes.h"
#include "screen.h"

class Menu : public Screen {
public:
	Menu();

	sf::String textReturn;

	void draw();
};

#endif
