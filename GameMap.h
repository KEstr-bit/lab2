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
	bool isWall(int coord_X, int coord_Y);
	bool isWall(double coord_X, double coord_Y);
	int whatIsWall(int coordX, int coordY);
	int whatIsWall(double coordX, double coordY);
};

