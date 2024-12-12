#include "GameMap.h"
#include "helper.h"

GameMap::GameMap(std::string worldMap[MAPSIZEX])
{
    for (int i = 0; i < MAPSIZEX; i++)
        this->worldMap[i] = worldMap[i];
}

GameMap::GameMap()
{
    worldMap[0] += "##########";
    worldMap[1] += "#........#";
    worldMap[2] += "#........#";
    worldMap[3] += "#........#";
    worldMap[4] += "#######..#";
    worldMap[5] += "#.....#..#";
    worldMap[6] += "#........#";
    worldMap[7] += "#...#....#";
    worldMap[8] += "#...#....#";
    worldMap[9] += "##########";
}

GameMap::~GameMap()
{
}

int GameMap::whatIsWall(int coordX, int coordY)
{
    if (coordX < 0 || coordX >= MAPSIZEX || coordY < 0 || coordY >= MAPSIZEY) {
        return 0; // Out of bounds is considered a wall
    }

    switch (worldMap[coordX][coordY])
    {
    case '#':
        return 0;
        break;
    case 'w':
        return 1;
        break;
    case 'k':
        return 2;
        break;
    case 'n':
        return 3;
        break;
    case 'd':
        return 4;
        break;
    default:
        return 0;
    }
}

int GameMap::whatIsWall(double coordX, double coordY)
{
    int x = helper::myRound(coordX);
    int y = helper::myRound(coordY);
    return whatIsWall(x, y);
}

bool GameMap::isWall(int coordX, int coordY)
{
    if (coordX < 0 || coordX >= MAPSIZEX || coordY < 0 || coordY >= MAPSIZEY) {
        return true; // Out of bounds is considered a wall
    }
    return worldMap[coordX][coordY] != '.';
};

bool GameMap::isWall(double cord_X, double cord_Y)
{
    int x = helper::myRound(cord_X);
    int y = helper::myRound(cord_Y);
    return isWall(x, y);
};