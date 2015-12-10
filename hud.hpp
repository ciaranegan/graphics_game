#ifndef _HUD_H_
#define _HUD_H_

#include "text.h"
#include <stdio.h>
#include <string.h>
#include <assert.h>

class HUD
{
public:

	int _lives_id, _level_id, _menu_id, _game_won_id;

	HUD(int gl_width, int gl_height);

	void startMenu();
	void restartMenu();
	void gameWon();
	void draw(int lives, int level);
};

#endif