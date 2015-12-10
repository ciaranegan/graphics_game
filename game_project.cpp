#include "obj_parser.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <iostream>
#include <math.h>
#include <assert.h>
#include <stdlib.h>
#include <array>
#include "stb_image.h"

#define GLM_FORCE_RADIANS

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "level.hpp"
#include "arrow.hpp"
#include "game.hpp"
#include "level_loader.hpp"

using namespace std;

// dimensions of the window drawing surface
int gl_width = 800;
int gl_height = 800;

//
// copy a shader from a plain text file into a character array
bool parse_file_into_str (const char* file_name, char* shader_str, int max_len)
{
    FILE* file = fopen (file_name , "r");
    int current_len = 0;
    char line[2048];
    
    shader_str[0] = '\0'; /* reset string */
    if (!file)
    {
        fprintf (stderr, "ERROR: opening file for reading: %s\n", file_name);
        return false;
    }
    strcpy (line, ""); /* remember to clean up before using for first time! */
    while (!feof (file))
    {
        if (NULL != fgets (line, 2048, file))
        {
            current_len += strlen (line); /* +1 for \n at end */
            if (current_len >= max_len)
            {
                fprintf (stderr, "ERROR: shader length is longer than string buffer length %i\n", max_len);
            }
            strcat (shader_str, line);
        }
    }
    if (EOF == fclose (file))
    { /* probably unnecesssary validation */
        fprintf (stderr, "ERROR: closing file from reading %s\n", file_name);
        return false;
    }
    return true;
}

int main ()
{
    GLFWwindow* window = NULL;
    const GLubyte* renderer;
    const GLubyte* version;
    GLuint shader_programme;
    GLuint chair_vao;
    GLuint meadow_vao;
    
    //
    // Start OpenGL using helper libraries
    // --------------------------------------------------------------------------
    if (!glfwInit ())
    {
        fprintf (stderr, "ERROR: could not start GLFW3\n");
        return 1;
    }
    
     glfwWindowHint (GLFW_CONTEXT_VERSION_MAJOR, 4);
     glfwWindowHint (GLFW_CONTEXT_VERSION_MINOR, 0);
     glfwWindowHint (GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
     glfwWindowHint (GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    
    window = glfwCreateWindow (gl_width, gl_height, "Hello Triangle", NULL, NULL);
    if (!window)
    {
        fprintf (stderr, "ERROR: opening OS window\n");
        return 1;
    }
    glfwMakeContextCurrent (window);
    
    glewExperimental = GL_TRUE;
    glewInit();
    
    /* get version info */
    renderer = glGetString (GL_RENDERER); /* get renderer string */
    version = glGetString (GL_VERSION); /* version as a string */
    printf ("Renderer: %s\n", renderer);
    printf ("OpenGL version supported %s\n", version);

//
// Load shaders from files
// --------------------------------------------------------------------------

    char* vertex_shader_str;
    char* fragment_shader_str;
    
    // allocate some memory to store shader strings
    vertex_shader_str = (char*)malloc (81920);
    fragment_shader_str = (char*)malloc (81920);
    // load shader strings from text files
    assert (parse_file_into_str ("game_project.vert", vertex_shader_str, 81920));
    assert (parse_file_into_str ("game_project.frag", fragment_shader_str, 81920));
    GLuint vs, fs;
    vs = glCreateShader (GL_VERTEX_SHADER);
    fs = glCreateShader (GL_FRAGMENT_SHADER);
    glShaderSource (vs, 1, (const char**)&vertex_shader_str, NULL);
    glShaderSource (fs, 1, (const char**)&fragment_shader_str, NULL);
    // free memory
    free (vertex_shader_str);
    free (fragment_shader_str);
    glCompileShader (vs);
    glCompileShader (fs);
    shader_programme = glCreateProgram ();
    glAttachShader (shader_programme, fs);
    glAttachShader (shader_programme, vs);
    glLinkProgram (shader_programme);

    LevelLoader* loader = new LevelLoader();

    Level** levels = (Level**)malloc(sizeof(Level*)*5);
    levels[0] = loader->loadLevel1();
    levels[1] = loader->loadLevel2();
    levels[2] = loader->loadLevel3();
    levels[3] = loader->loadLevel4();
    levels[4] = loader->loadLevel5();

    glm::vec3 position = glm::vec3(0, 20, 10); // Position of the camera    
    
    Game* game = new Game(levels, 5, position);
    Arrow* arrow = new Arrow();
    game->_arrow = arrow;

    glEnable (GL_DEPTH_TEST); // enable depth-testing
    glDepthFunc (GL_LESS); // depth-testing interprets a smaller value as "closer"
    glClearColor (0.2, 0.2, 0.2, 1.0);

    int M_loc, V_loc, P_loc;
  
    double FPS = 35.0;
    double current_time = glfwGetTime();

    M_loc = glGetUniformLocation(shader_programme, "M");
    V_loc = glGetUniformLocation(shader_programme, "V");
    P_loc = glGetUniformLocation(shader_programme, "P");

    while (!glfwWindowShouldClose(window) && game->_state != EndGame)
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glUseProgram(shader_programme);
        glfwPollEvents();

        if (GLFW_PRESS == glfwGetKey (window, GLFW_KEY_ESCAPE))
        {
            glfwSetWindowShouldClose (window, 1);
        }

        game->update(window);
        game->draw(shader_programme, V_loc, P_loc, M_loc);

        glfwSwapBuffers(window);

        while(glfwGetTime() < current_time + (1 / FPS));
        current_time = glfwGetTime();
        
    }
    
    return 0;
}