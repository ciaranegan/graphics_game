#ifndef _BALL_H_
#define _BALL_H_

#include "mesh.hpp"
#include "bomb.hpp"
#include <iostream>
#include <math.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#define GLM_FORCE_RADIANS

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Ball
{
public:
	double _xpos, _ypos, _speed;

	bool _collided;

	glm::mat4 _V, _P, _M;

	int _texture_offset;

	Ball(double speed, double xpos, double ypos);
	void draw(int shader_programme, int V_loc, int P_loc, int M_loc);
	void update(GLFWwindow* window, glm::vec3 position, Bomb* bomb[], int no_of_bombst);
	// bool hasCollided(Bomb* bomb);
};

#endif