#ifndef _BINDINGS_H
#define _BINDINGS_H

#include "includes.h"

void setupKeyBindings();

void quitGame(sf::Event ev, bool real);

void lookAround(sf::Event ev, bool real);

void strafeFwd(sf::Event, bool);
void strafeBack(sf::Event, bool);
void strafeLeft(sf::Event, bool);
void strafeRight(sf::Event, bool);

void setScreen_game(sf::Event, bool);
void setScreen_menu(sf::Event, bool);

#endif
