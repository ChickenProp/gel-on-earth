#ifndef _SCREEN_H
#define _SCREEN_H

#include "keymap.h"

enum Screens { game, menu };

class Screen {
public:
	Screen();

	Keymap keymap;

	virtual void update();
	virtual void draw();
};

#endif
