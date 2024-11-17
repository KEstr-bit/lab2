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

bool GameMap::isWall(int coordX, int coordY)
{
    if (coordX < 0 || coordX >= MAPSIZEX || coordY < 0 || coordY >= MAPSIZEY) {
        return true; // Out of bounds is considered a wall
    }
    return worldMap[coordX][coordY] == '#';
};

bool GameMap::isWall(double coord_X, double coord_Y)
{
    int x = myRound(coord_X);
    int y = myRound(coord_Y);
    return isWall(x, y);
};