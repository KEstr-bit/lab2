#pragma once

#define MAP_SIZE_X 10
#define MAP_SIZE_Y 10

class GameMap
{
public:
	GameMap(char pre_Map[MAP_SIZE_X][MAP_SIZE_Y]);
	GameMap();
	~GameMap();
	int getWorldMap(char get_Map[MAP_SIZE_X][MAP_SIZE_Y]);

private:
	char* worldMap;              //карта
};

