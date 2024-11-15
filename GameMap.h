#pragma once
#include <string>

class GameMap
{
public:
	static const int MAPSIZEX = 10;
	static const int MAPSIZEY = 10;

private:
	std::string worldMap[MAPSIZEY];              //карта

public:
	GameMap(std::string worldMap[MAPSIZEX]);
	GameMap();
	~GameMap();
	bool isWall(int coord_X, int coord_Y);
	bool isWall(double coord_X, double coord_Y);
};

