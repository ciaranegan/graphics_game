#ifndef _MESH_H_
#define _MESH_H_

#include "obj_parser.h"
#include <GL/glew.h>
#include <iostream>
#include "stb_image.h"

class Mesh
{
public:
	int _point_count;
	GLfloat* _vertices;
	GLfloat* _normals;
	GLfloat* _textures;

	GLuint _vao, _vertex_buffer, _normals_buffer, _textures_buffer;

	Mesh(const char* file_name);
	void loadTextures(const char* file_name, int texture_offset);
};

#endif