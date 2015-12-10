#include "arrow.hpp"

Arrow::Arrow()
{
	_mesh = new Mesh("blender/arrow.obj");
    _mesh->loadTextures("images/blue.png", 3);

	_texture_offset = 3;
	_animation = 0.0f;
	_direction = true;
}

void Arrow::draw(int shader_programme, int V_loc, int P_loc, int M_loc)
{
	GLuint texture_location = glGetUniformLocation(shader_programme, "basic_texture");
    glUniform1i(texture_location, _texture_offset);
    glBindVertexArray(_mesh->_vao);

    glUniformMatrix4fv(V_loc, 1, GL_FALSE, glm::value_ptr(_V));
    glUniformMatrix4fv(P_loc, 1, GL_FALSE, glm::value_ptr(_P));
    glUniformMatrix4fv(M_loc, 1, GL_FALSE, glm::value_ptr(_M));

    glDrawArrays(GL_TRIANGLES, 0, _mesh->_point_count);
}

void Arrow::update(GLFWwindow* window, glm::vec3 position)
{
	_V = glm::lookAt(position, glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
	_P = glm::perspective(45.0f, 1.0f, 0.1f, 100.0f);
	_M = glm::scale(glm::mat4(1.0), glm::vec3(0.5, 0.5, 0.5));
	_M = glm::translate(_M, glm::vec3(16, 2 + (2 * _animation), 14));
	_M = glm::rotate(_M, (float)M_PI/2.0f, glm::vec3(0.0f, 0.0f, 1.0f));
	
	if (_animation > M_PI)
	{
		_direction = false;
	}
	if (_animation < 0)
	{
		_direction = true;
	}
	if (_direction)
	{
		_animation += 0.05f;
	}
	else
	{
		_animation -= 0.05f;
	}
}