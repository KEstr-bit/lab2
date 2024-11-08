#include "GameMap.h"
#include <iostream>
#include "helper.h"

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

bool GameMap::isWall(int coord_X, int coord_Y)
{
    if (worldMap[coord_X][coord_Y] == '#')
        return true;
    else
        return false;
};

bool GameMap::isWall(double coord_X, double coord_Y)
{
    int x = roundd(coord_X);
    int y = roundd(coord_Y);
    if (worldMap[x][y] == '#')
        return true;
    else
        return false;
};