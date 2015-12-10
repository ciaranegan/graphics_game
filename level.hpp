#ifndef _LEVEL_H_
#define _LEVEL_H_

#include "mesh.hpp"
#include "bomb.hpp"
#include "ball.hpp"
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#define GLM_FORCE_RADIANS

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

enum LevelState
{
	Start,
	InProgress,
	Finished,
	Completed,
	LevelOver
};

enum CameraPosition
{
	Bottom = 0,
	Left = 1,
	Top = 2,
	Right = 3
};

class Level
{
public:

	glm::mat4 _V, _P, _M;

	Bomb** _bombs;
	Ball* _ball;

	float _rotation;

	CameraPosition _camera_state;
	LevelState _state;

	double _start_xpos, _start_ypos;
	double _end_xpos, _end_ypos;

	int _level_number, _lives, _bomb_count, _texture_offset;

	Level(Ball* ball, Bomb** bombs, int bomb_count, double endx, double endy);
	void update(GLFWwindow* window, glm::vec3 position);
	void draw(int shader_programme, int V_loc, int P_loc, int M_loc);
	bool levelWon();
	bool hasCollided();
};

#endif