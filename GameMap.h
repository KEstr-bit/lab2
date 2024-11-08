#pragma once
#include <string>

class GameMap
{
public:
	GameMap();
	~GameMap();
	bool isWall(int coord_X, int coord_Y);
	bool isWall(double coord_X, double coord_Y);

public:
	static const int MAPSIZEX = 10;
	static const int MAPSIZEY = 10;

private:
	std::string worldMap[MAPSIZEY];              //карта

};

