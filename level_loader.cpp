#include "level_loader.hpp"

Level* LevelLoader::loadLevel1()
{

	Ball* ball = new Ball(2.5, 0.0, 0.0);

	Bomb* b1 = new Bomb(5.0, 48, 51, Vertical, true);
	Bomb* b2 = new Bomb(5.0, 8, 16, Vertical, true);
	Bomb* b3 = new Bomb(5.0, 16, 24, Vertical, true);
	Bomb* b4 = new Bomb(5.0, 24, 32, Vertical, true);
	Bomb* b5 = new Bomb(5.0, 32, 40, Vertical, true);
	Bomb* b6 = new Bomb(5.0, 40, 48, Vertical, true);

	Bomb** bombs = (Bomb**)malloc(sizeof(Bomb*)*6);
	bombs[0] = b1;
	bombs[1] = b2;
	bombs[2] = b3;
	bombs[3] = b4;
	bombs[4] = b5;
	bombs[5] = b6;

	Level* level = new Level(ball, bombs, 6, 54.0, 54.0);
	return level;
}

Level* LevelLoader::loadLevel2()
{
	Ball* ball = new Ball(2.5, 0.0, 0.0);

	Bomb* b1 = new Bomb(5.6, 0, 16, Horizontal, true);
	Bomb* b2 = new Bomb(5.6, 0, 32, Horizontal, true);
	Bomb* b3 = new Bomb(5.6, 0, 48, Horizontal, true);
	Bomb* b4 = new Bomb(5.6, 16, 0, Vertical, true);
	Bomb* b5 = new Bomb(5.6, 32, 0, Vertical, true);
	Bomb* b6 = new Bomb(5.6, 48, 0, Vertical, true);

	Bomb** bombs = (Bomb**)malloc(sizeof(Bomb*)*6);
	bombs[0] = b1;
	bombs[1] = b2;
	bombs[2] = b3;
	bombs[3] = b4;
	bombs[4] = b5;
	bombs[5] = b6;

	Level* level = new Level(ball, bombs, 6, 54.0, 54.0);
	return level;
}

Level* LevelLoader::loadLevel3()
{
	Ball* ball = new Ball(3.0, 0.0, 0.0);

	Bomb* b1 = new Bomb(6.2, 7, 10, Horizontal, true);
	Bomb* b2 = new Bomb(6.2, 14, 15, Horizontal, true);
	Bomb* b3 = new Bomb(6.2, 20, 20, Horizontal, true);
	Bomb* b4 = new Bomb(6.2, 25, 25, Horizontal, true);
	Bomb* b5 = new Bomb(6.2, 30, 30, Horizontal, true);
	Bomb* b6 = new Bomb(6.2, 36, 35, Horizontal, true);
	Bomb* b7 = new Bomb(6.2, 43, 40, Horizontal, true);
	Bomb* b8 = new Bomb(6.2, 50, 45, Horizontal, true);

	Bomb** bombs = (Bomb**)malloc(sizeof(Bomb*)*8);
	bombs[0] = b1;
	bombs[1] = b2;
	bombs[2] = b3;
	bombs[3] = b4;
	bombs[4] = b5;
	bombs[5] = b6;
	bombs[6] = b7;
	bombs[7] = b8;

	Level* level = new Level(ball, bombs, 8, 54.0, 54.0);
	return level;
}

Level* LevelLoader::loadLevel4()
{
	Ball* ball = new Ball(3.0, 0.0, 0.0);

	Bomb* b1 = new Bomb(6.6, 10, 10, Horizontal, true);
	Bomb* b2 = new Bomb(6.6, 15, 15, Horizontal, false);
	Bomb* b3 = new Bomb(6.6, 20, 20, Horizontal, true);
	Bomb* b4 = new Bomb(6.6, 25, 25, Horizontal, false);
	Bomb* b5 = new Bomb(6.6, 30, 30, Vertical, true);
	Bomb* b6 = new Bomb(6.6, 35, 35, Vertical, false);
	Bomb* b7 = new Bomb(6.6, 9, 40, Vertical, true);
	Bomb* b8 = new Bomb(6.6, 20, 45, Vertical, false);

	Bomb** bombs = (Bomb**)malloc(sizeof(Bomb*)*8);
	bombs[0] = b1;
	bombs[1] = b2;
	bombs[2] = b3;
	bombs[3] = b4;
	bombs[4] = b5;
	bombs[5] = b6;
	bombs[6] = b7;
	bombs[7] = b8;

	Level* level = new Level(ball, bombs, 8, 54.0, 54.0);
	return level;
}

Level* LevelLoader::loadLevel5()
{
	Ball* ball = new Ball(3.5, 0.0, 0.0);

	Bomb* b1 = new Bomb(7.2, 9, 13, Horizontal, true);
	Bomb* b2 = new Bomb(7.2, 11, 15, Horizontal, false);
	Bomb* b3 = new Bomb(7.2, 22, 25, Horizontal, true);
	Bomb* b4 = new Bomb(7.2, 28, 29, Horizontal, false);
	Bomb* b5 = new Bomb(7.2, 37, 37, Vertical, true);
	Bomb* b6 = new Bomb(7.2, 31, 33, Vertical, false);
	Bomb* b7 = new Bomb(7.2, 20, 40, Vertical, true);
	Bomb* b8 = new Bomb(7.2, 45, 45, Vertical, false);
	Bomb* b9 = new Bomb(7.2, 16, 20, Horizontal, true);
	Bomb* b10 = new Bomb(7.2, 8, 46, Vertical, false);

	Bomb** bombs = (Bomb**)malloc(sizeof(Bomb*)*10);
	bombs[0] = b1;
	bombs[1] = b2;
	bombs[2] = b3;
	bombs[3] = b4;
	bombs[4] = b5;
	bombs[5] = b6;
	bombs[6] = b7;
	bombs[7] = b8;
	bombs[8] = b9;
	bombs[9] = b10;

	Level* level = new Level(ball, bombs, 8, 54.0, 54.0);
	return level;
}