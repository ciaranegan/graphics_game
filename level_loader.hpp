#ifndef _LEVEL_LOADER_H
#define _LEVEL_LOADER_H

#include "mesh.hpp"
#include "level.hpp"
#include "bomb.hpp"
#include "ball.hpp"

class LevelLoader
{
public:

	Level* loadLevel1();
	Level* loadLevel2();
	Level* loadLevel3();
	Level* loadLevel4();
	Level* loadLevel5();
};

#endif