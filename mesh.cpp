#include "mesh.hpp"

Mesh::Mesh(const char* file_name)
{

    _point_count = 0;

    _vertices = NULL; // array of vertex points
    _normals = NULL; // array of vertex normals 
    _textures = NULL; // array of texture coordinates
    if (!load_obj_file (file_name, _vertices, _textures, _normals, _point_count))
    {
        std::cout << "ERROR: coutd not find mesh file" << std::endl;
    }


	glGenBuffers (1, &_vertex_buffer);
    glBindBuffer (GL_ARRAY_BUFFER, _vertex_buffer);
    glBufferData (GL_ARRAY_BUFFER, sizeof (float) * 3 * _point_count, _vertices, GL_STATIC_DRAW);

    glGenBuffers (1, &_normals_buffer);
    glBindBuffer (GL_ARRAY_BUFFER, _normals_buffer);
    glBufferData (GL_ARRAY_BUFFER, sizeof (float) * 3 * _point_count, _normals, GL_STATIC_DRAW);

    glGenBuffers (1, &_textures_buffer);
    glBindBuffer (GL_ARRAY_BUFFER, _textures_buffer);
    glBufferData (GL_ARRAY_BUFFER, sizeof (float) * 2 * _point_count, _textures, GL_STATIC_DRAW);

    glGenVertexArrays (1, &_vao);
    glBindVertexArray (_vao);

    glEnableVertexAttribArray (0);
    glBindBuffer (GL_ARRAY_BUFFER, _vertex_buffer);
    glVertexAttribPointer (0, 3, GL_FLOAT, GL_FALSE, 0, NULL);

    glEnableVertexAttribArray (1);
    glBindBuffer (GL_ARRAY_BUFFER, _normals_buffer);
    glVertexAttribPointer (1, 3, GL_FLOAT, GL_FALSE, 0, NULL);

    glEnableVertexAttribArray (2);
    glBindBuffer (GL_ARRAY_BUFFER, _textures_buffer);
    glVertexAttribPointer (2, 2, GL_FLOAT, GL_FALSE, 0, NULL);
}

void Mesh::loadTextures(const char* file_name, int texture_offset)
{
    int texture_width, texture_height, c;

    unsigned char* texture = stbi_load(file_name, &texture_width, &texture_height, &c, STBI_rgb_alpha);

    if (texture == NULL)
    {
        std::cout << "ERROR: Texture didn't load" << std::endl;
    }

    glEnable(GL_TEXTURE_2D);
    glGenTextures(1, &_textures_buffer);
    glActiveTexture(GL_TEXTURE0 + texture_offset);
    glBindTexture(GL_TEXTURE_2D, _textures_buffer);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, texture_width, texture_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, texture);
    glGenerateMipmap(GL_TEXTURE_2D);

    stbi_image_free(texture);
}