#include "game.hpp"

#define ANIMATION_LENGTH 10.0f

glm::vec3 CAMERA_POSITIONS[4] = {
	glm::vec3(0, 20, 10),
	glm::vec3(-10, 20, 0),
	glm::vec3(0, 20, -10),
	glm::vec3(10, 20, 0)
};

Game::Game(Level** levels, int level_count, glm::vec3 position)
{
	_current_level = 1;
	_levels = levels;
	_level_count = level_count;
	_state = Menu;
	_hud = new HUD(800, 800);
	_camera_position = position;
	_camera_moving = false;
	_current_camera_destination_pos = position;
	_current_animation_start_pos = position;
	_current_animation_iteration = 0;
	_current_position_index = 0;
}

void Game::update(GLFWwindow* window)
{
	switch(_state)
	{
		case Menu:
			if (glfwGetKey(window, GLFW_KEY_ENTER) == GLFW_PRESS)
			{
				_state = GameStart;
			}
			break;

		case GameStart:
			_current_level = 1;
			_levels[_current_level-1]->_state = Start;
			_levels[_current_level-1]->_lives = 3;
			_state = GameInProgress;
			_levels[_current_level-1]->update(window, _camera_position);
			_arrow->update(window, _camera_position);
			break;

		case GameInProgress:
			if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
            {
            	if (!_camera_moving)
				{
	                _camera_moving = true;
	                _current_animation_start_pos = _camera_position;
	                if (_current_position_index != 3)
	                {
	                	_current_position_index ++;
	                	_current_camera_destination_pos = CAMERA_POSITIONS[_current_position_index];
	                }
	                else
	                {
	                	_current_position_index = 0;
	                	_current_camera_destination_pos = CAMERA_POSITIONS[_current_position_index];
	                }
	                _camera_position = animateCamera();
            	}
            }
            if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
            {
            	if (!_camera_moving)
				{
	                _camera_moving = true;
	                _current_animation_start_pos = _camera_position;
	                if (_current_position_index != 0)
	                {
	                	_current_position_index --;
	                	_current_camera_destination_pos = CAMERA_POSITIONS[_current_position_index];
	                }
	                else
	                {
	                	_current_position_index = 3;
	                	_current_camera_destination_pos = CAMERA_POSITIONS[_current_position_index];
	                }
	                _camera_position = animateCamera();
            	}
            }
			
			if (_camera_moving)
			{
				_camera_position = animateCamera();
			}

			switch(_levels[_current_level-1]->_state)
			{
				case LevelOver:
					_state = GameOver;
					break;

				case Completed:
					if (_current_level == _level_count)
					{
						_state = GameCompleted;
					}
					else
					{
						_levels[_current_level-1]->_state = Finished;
						_current_level ++;
						_levels[_current_level-1]->_lives = 3;
						_levels[_current_level-1]->_state = Start;
					}
					break;

				default:
					_levels[_current_level-1]->update(window, _camera_position);
					_arrow->update(window, _camera_position);
					break;
			}
			break;

		case GameCompleted:
			if (glfwGetKey(window, GLFW_KEY_ENTER) == GLFW_PRESS)
			{
				_state = GameStart;
			}
			break;

		case GameOver:
			if (glfwGetKey(window, GLFW_KEY_ENTER) == GLFW_PRESS)
			{
				_state = GameStart;
			}
			break;
	}
}

glm::vec3 Game::animateCamera()
{
	float start_x = _current_animation_start_pos.x;
	float start_z = _current_animation_start_pos.z;

	float end_x = _current_camera_destination_pos.x;
	float end_z = _current_camera_destination_pos.z;

	float new_x = start_x + (end_x - start_x) * float((float)_current_animation_iteration / ANIMATION_LENGTH);
	float new_z = start_z + (end_z - start_z) * float((float)_current_animation_iteration / ANIMATION_LENGTH);

	glm::vec3 camera = glm::vec3(new_x, _current_camera_destination_pos.y, new_z);
	_current_animation_iteration++;

	if (_current_animation_iteration > ANIMATION_LENGTH)
	{
		_camera_moving = false;
		_current_animation_iteration = 0;
	}

	return camera;
}

void Game::draw(int shader_programme, int V_loc, int P_loc, int M_loc)
{
	if (_state == GameInProgress && _levels[_current_level-1]->_state == InProgress)
	{
		_arrow->draw(shader_programme, V_loc, P_loc, M_loc);
		_levels[_current_level-1]->draw(shader_programme, V_loc, P_loc, M_loc);
		_hud->draw(_levels[_current_level-1]->_lives, _current_level);
	}	

	if (_state == Menu)
	{
		_hud->startMenu();
	}
	
	if (_state == GameOver)
	{
		_hud->restartMenu();
	}

	if (_state == GameCompleted)
	{
		_hud->gameWon();
	}
}