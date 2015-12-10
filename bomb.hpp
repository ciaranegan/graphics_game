#ifndef _BOMB_H_
#define _BOMB_H_

#include "mesh.hpp"
#include <GL/glew.h>

#define GLM_FORCE_RADIANS

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


enum BombType
{
	Vertical,
	Horizontal
};

class Bomb
{
public:
	double _xpos, _ypos, _speed;
	bool _direction;

	int _texture_offset;

	BombType _type;

	glm::mat4 _V, _P, _M;

	Bomb(double speed, double x_pos, double y_pos, BombType type, bool direction);
	void update(glm::vec3 position);
	void draw(int shader_programme, int V_loc, int P_loc, int M_loc);
};

#endif