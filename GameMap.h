#pragma once
#include <string>

class GameMap
{
public:
	static constexpr int MAP_SIZE_X = 10;			
	static constexpr int MAP_SIZE_Y = 10;			

private:
	std::string worldMap[MAP_SIZE_Y];         

public:
	explicit GameMap(std::string worldMap[MAP_SIZE_X]);
	bool isWall(double cordX, double cordY);
	bool isWall(int cordX, int cordY);
	int whatIsWall(double cordX, double cordY);
	int whatIsWall(int cordX, int cordY);
	
};

