#include "bomb.hpp"
#include <iostream>

static Mesh* _mesh = NULL;

Bomb::Bomb(double speed, double x_pos, double y_pos, BombType type, bool direction)
{
	if (_mesh == NULL)
	{
		_mesh = new Mesh("blender/ball.obj");
		_mesh->loadTextures("images/red.png", 2);
	}

	_speed = speed;
	_xpos = x_pos;
	_ypos = y_pos;
	_type = type;
	_direction = direction;
	_texture_offset = 2;
}

void Bomb::draw(int shader_programme, int V_loc, int P_loc, int M_loc)
{
	GLuint texture_location = glGetUniformLocation(shader_programme, "basic_texture");
    glUniform1i(texture_location, _texture_offset);
    glBindVertexArray(_mesh->_vao);

    glUniformMatrix4fv(V_loc, 1, GL_FALSE, glm::value_ptr(_V));
    glUniformMatrix4fv(P_loc, 1, GL_FALSE, glm::value_ptr(_P));
    glUniformMatrix4fv(M_loc, 1, GL_FALSE, glm::value_ptr(_M));

    glDrawArrays(GL_TRIANGLES, 0, _mesh->_point_count);
}

void Bomb::update(glm::vec3 position)
{
	if (_type == Vertical)
	{
		if (_direction)
		{
			_ypos += 0.5 * _speed;
			if (_ypos > 56)
			{
				_direction = false;
				_ypos = 56;
			}
		}
		else
		{
			_ypos -= 0.5 * _speed;
			if (_ypos < 0)
			{
				_direction = true;
				_ypos = 0;
			}
		}
	}
	else
	{
		if (_direction)
		{
			_xpos += 0.5 * _speed;
			if (_xpos > 56.5)
			{
				_direction = false;
				_xpos = 56.5;
			}
		}
		else
		{
			_xpos -= 0.5 * _speed;
			if (_xpos < 0)
			{
				_direction = true;
				_xpos = 0;
			}
		}
	}

	_V = glm::lookAt(position, glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));

	_P = glm::perspective(45.0f, 1.0f, 0.1f, 100.0f);

	_M = glm::scale(glm::mat4(1.0), glm::vec3(0.25, 0.25, 0.25));
	_M = glm::translate(_M, glm::vec3(-29.5+_xpos, 2.5, -27+_ypos));
}