#include "GameMap.h"
#include "Helper.h"

GameMap::GameMap(std::string worldMap[MAP_SIZE_X])
{
    for (int i = 0; i < MAP_SIZE_X; i++)
        this->worldMap[i] = worldMap[i];
}


int GameMap::whatIsWall(const int cordX, const int cordY)
{
    if (cordX < 0 || cordX >= MAP_SIZE_X || cordY < 0 || cordY >= MAP_SIZE_Y) {
        return 0;
    }

    switch (worldMap[cordX][cordY])
    {
    case '#':
        return 0;
    case 'w':
        return 1;
    case 'k':
        return 2;
    case 'n':
        return 3;
    case 'd':
        return 4;
    default:
        return 0;
    }
}

int GameMap::whatIsWall(const double cordX, const double cordY)
{
	const int x = static_cast<int>(Helper::round(cordX));
	const int y = static_cast<int>(Helper::round(cordY));
    return whatIsWall(x, y);
}

bool GameMap::isWall(const int cordX, const int cordY)
{
    if (cordX < 0 || cordX >= MAP_SIZE_X || cordY < 0 || cordY >= MAP_SIZE_Y) {
        return true;
    }
    return worldMap[cordX][cordY] != '.';
};

bool GameMap::isWall(const double cordX, const double cordY)
{
	const int x = static_cast<int>(Helper::round(cordX));
	const int y = static_cast<int>(Helper::round(cordY));
    return isWall(x, y);
};