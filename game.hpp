#ifndef _GAME_H_
#define _GAME_H_

#include "arrow.hpp"
#include "level.hpp"
// #include "background.hpp"

#include "hud.hpp"
#include <GLFW/glfw3.h>

enum GameState
{
	Menu,
	GameStart,
	GameInProgress,
	GameCompleted,
	GameOver,
	EndGame
};

class Game
{
public:

	Level** _levels;

	glm::vec3 _camera_position, _current_camera_destination_pos, _current_animation_start_pos;

	HUD* _hud;

	Arrow* _arrow;

	bool _camera_moving;

	int _current_level, _level_count, _current_animation_iteration, _current_position_index;
	
	GameState _state;

	Game(Level** levels, int level_count, glm::vec3 position);
	void update(GLFWwindow* window);
	void draw(int shader_programme, int V_loc, int P_loc, int M_loc);
	glm::vec3 animateCamera();
};

#endif