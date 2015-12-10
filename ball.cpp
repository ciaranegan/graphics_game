
#include "ball.hpp"

static Mesh* _mesh = NULL;

Ball::Ball(double speed, double xpos, double ypos)
{
    if (_mesh == NULL)
    {
        _mesh = new Mesh("blender/ball.obj");
        _mesh->loadTextures("images/green.png", 4);

    }
	_speed = speed;
	_xpos = xpos;
	_ypos = ypos;
    _texture_offset = 4;
}

void Ball::update(GLFWwindow* window, glm::vec3 position, Bomb* bombs[], int bomb_count)
{
	if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
    {
        if (position == glm::vec3(0, 20, 10))
        {
            _ypos = fmax(0, _ypos - (0.5 * _speed));
        }
        else if (position == glm::vec3(-10, 20, 0))
        {
            _xpos = fmin(56.5, _xpos + (0.5 * _speed));
        }
        else if (position == glm::vec3(0, 20, -10))
        {
            _ypos = fmin(56, _ypos + (0.5 * _speed));
        }
        else
        {
            _xpos = fmax(_xpos - (0.5 * _speed), 0);
        }
        
    }

    if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
    {
        if (position == glm::vec3(0, 20, 10))
        {  
            _ypos = fmin(56, _ypos + (0.5 * _speed));
        }
        else if (position == glm::vec3(-10, 20, 0))
        {
            _xpos = fmax(_xpos - (0.5 * _speed), 0);
            
        }
        else if (position == glm::vec3(0, 20, -10))
        {
            _ypos = fmax(0, _ypos - (0.5 * _speed));
        }
        else
        {
            _xpos = fmin(56.5, _xpos + (0.5 * _speed));
        }
    }

    if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
    {
        if (position == glm::vec3(0, 20, 10))
        {
            _xpos = fmin(56.5, _xpos + (0.5 * _speed));
        }
        else if (position == glm::vec3(-10, 20, 0))
        {
            _ypos = fmin(56, _ypos + (0.5 * _speed));
        }
        else if (position == glm::vec3(0, 20, -10))
        {
            _xpos = fmax(_xpos - (0.5 * _speed), 0);
        }
        else
        {
            _ypos = fmax(0, _ypos - (0.5 * _speed));
        }
        
    }

    if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
    {
        if (position == glm::vec3(0, 20, 10))
        {
            _xpos = fmax(_xpos - (0.5 * _speed), 0);
        }
        else if (position == glm::vec3(-10, 20, 0))
        {
            _ypos = fmax(0, _ypos - (0.5 * _speed));
        }
        else if (position == glm::vec3(0, 20, -10))
        {
            _xpos = fmin(56.5, _xpos + (0.5 * _speed));
        }
        else
        {
            _ypos = fmin(56, _ypos + (0.5 * _speed));
        }
    }

    _V = glm::lookAt(position, glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
	_P = glm::perspective(45.0f, 1.0f, 0.1f, 100.0f);
	_M = glm::scale(glm::mat4(1.0), glm::vec3(0.25, 0.25, 0.25));
	_M = glm::translate(_M, glm::vec3(-29.5+_xpos, 2.5, -27+_ypos));
}

void Ball::draw(int shader_programme, int V_loc, int P_loc, int M_loc)
{
	GLuint texture_location = glGetUniformLocation(shader_programme, "basic_texture");
    glUniform1i(texture_location, _texture_offset);
    glBindVertexArray(_mesh->_vao);

    glUniformMatrix4fv(V_loc, 1, GL_FALSE, glm::value_ptr(_V));
    glUniformMatrix4fv(P_loc, 1, GL_FALSE, glm::value_ptr(_P));
    glUniformMatrix4fv(M_loc, 1, GL_FALSE, glm::value_ptr(_M));

    glDrawArrays(GL_TRIANGLES, 0, _mesh->_point_count);
}