#pragma once
#include <string>

class GameMap
{
public:
	static const int MAPSIZEX = 10;			//размер карты по X
	static const int MAPSIZEY = 10;			//размер карты по Y

private:
	std::string worldMap[MAPSIZEY];         //карта

public:
	GameMap(std::string worldMap[MAPSIZEX]);
	GameMap();
	~GameMap();
	//проверка на стену
	bool isWall(int cord_X, int cord_Y);
	bool isWall(double cord_X, double cord_Y);
	int whatIsWall(int cordX, int cordY);
	int whatIsWall(double cordX, double cordY);
};

