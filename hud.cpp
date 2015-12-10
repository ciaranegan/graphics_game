#include "hud.hpp"

HUD::HUD(int gl_width, int gl_height)
{
	assert(init_text_rendering ("freemono.png", "freemono.meta", gl_width, gl_height));
}

void HUD::draw(int lives, int level)
{

	_lives_id = add_text("Lives Remaining: ", 0.0f, 1.0f, 75.0f, 0.0f, 0.8f, 0.2f, 0.5f);
	_level_id = add_text("Level: ", -1.0f, 1.0f, 75.0f, 1.0f, 0.0f, 0.0f, 1.0f);

	int a, b;
	char lives_str[50];
	char level_str[50];
	sprintf(lives_str, "Lives Remaining: %d", lives);
	sprintf(level_str, "Level: %d", level);
	update_text(_lives_id, lives_str);
	update_text(_level_id, level_str);

	draw_texts();

	remove_text();
	remove_text();
}

void HUD::startMenu()
{
	_menu_id = add_text("Welcome to Bomb Dodger.\n"
			"Move the ball to the corner with the arrow in it\n"
			"while avoiding the red bombs.\n"
			"Arrow keys to move and A&D keys to change camera angle.\n"
			"Press Enter to begin",
						-0.90f, 0.5f, 50.0f, 1.0f, 1.0f, 1.0f, 1.0f);

	draw_texts();
	remove_text();
}

void HUD::restartMenu()
{
	_menu_id = add_text("Game over...\nPress Enter to restart",
						-0.75f, 0.5f, 100.0f, 1.0f, 0.0f, 0.0f, 1.0f);

	draw_texts();
	remove_text();
}

void HUD::gameWon()
{
	_game_won_id = add_text("Congratulations!\nYou Won!\nPress Enter to restart",
					-0.75f, 0.5f, 100.0f, 1.0f, 0.0f, 0.0f, 1.0f);

	draw_texts();
	remove_text();
}