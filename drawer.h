#pragma once
#include "map.h"
#include "game.h"

class drawer
{
public:
	int draw(char world_Map[MAP_SIZE_X][MAP_SIZE_Y], game* gm);
	drawer();
	~drawer();

private:
	char* firstBuffer;
	char* secondBuffer;
};

