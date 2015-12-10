#include "level.hpp"

static Mesh* _mesh = NULL;

Level::Level(Ball* ball, Bomb** bombs, int bomb_count, double endx, double endy)
{
    _texture_offset = 1;
	if (_mesh == NULL)
    {
        _mesh = new Mesh("blender/empty_level.obj");
        _mesh->loadTextures("images/WoodPlanksClean.jpg", _texture_offset);
    }
    _ball = ball;
    _bombs = bombs;
    _end_xpos = endx;
    _end_ypos = endy;
    _lives = 3;
    _bomb_count = bomb_count;
    _state = Start;
    _rotation = 0.0f;
    _camera_state = Bottom;
    
}

bool Level::hasCollided()
{
    for (int i = 0; i < _bomb_count; i ++)
    {
        if (abs(_bombs[i]->_xpos - _ball->_xpos) < 1.5 && abs(_bombs[i]->_ypos - _ball->_ypos) < 1.5)
        {
            return true;
        }
    }
    return false;
}

void Level::update(GLFWwindow* window, glm::vec3 position)
{
    switch(_state)
    {
        case Start:
            _ball->_xpos = 0.0;
            _ball->_ypos = 0.0;
            _state = InProgress;
            break;

        case InProgress:
            if (hasCollided())
            {
                _state = Finished;
                break;
            }
            if (levelWon())
            {
                _state = Completed;
            }

            
            for (int i = 0; i < _bomb_count; i ++)
            {
                _bombs[i]->update(position);
            }

            _ball->update(window, position, _bombs, _bomb_count);

            _V = glm::lookAt(position, glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
            _P = glm::perspective(45.0f, 1.0f, 0.1f, 100.0f);
            _M = glm::mat4(1.0);
            break;

        case Finished:
            _lives --;
            if (_lives <= 0)
            {
                _state = LevelOver;
            }
            else
            {
                _state = Start;
            }
        case LevelOver:
            break;
        case Completed:
            break;
    }
}

bool Level::levelWon()
{
    if (_ball->_xpos > _end_xpos && _ball->_ypos > _end_ypos)
    {
        return true;
    }
    return false;
}

void Level::draw(int shader_programme, int V_loc, int P_loc, int M_loc)
{
    for (int i = 0; i < _bomb_count; i ++)
    {
        _bombs[i]->draw(shader_programme, V_loc, P_loc, M_loc);
    }

    _ball->draw(shader_programme, V_loc, P_loc, M_loc);

    GLuint texture_location = glGetUniformLocation(shader_programme, "basic_texture");
    glUniform1i(texture_location, _texture_offset);
    glBindVertexArray(_mesh->_vao);

    glUniformMatrix4fv(V_loc, 1, GL_FALSE, glm::value_ptr(_V));
    glUniformMatrix4fv(P_loc, 1, GL_FALSE, glm::value_ptr(_P));
    glUniformMatrix4fv(M_loc, 1, GL_FALSE, glm::value_ptr(_M));

    glDrawArrays(GL_TRIANGLES, 0, _mesh->_point_count);
}