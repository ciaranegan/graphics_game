#ifndef _ARROW_H_
#define _ARROW_H_

#include "mesh.hpp"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#define GLM_FORCE_RADIANS

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Arrow
{
public:

	glm::mat4 _V, _P, _M;

	Mesh* _mesh;

	Arrow();

	float _animation;
	bool _direction;

	int _texture_offset;

	void update(GLFWwindow* window, glm::vec3 position);
	void draw(int shader_programme, int V_loc, int P_loc, int M_loc);
};

#endif