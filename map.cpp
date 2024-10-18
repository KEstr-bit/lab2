#include "map.h"
#include <iostream>

map::map(char pre_Map[MAP_SIZE_X][MAP_SIZE_Y])
{
    for (int x = 0; x < MAP_SIZE_X; x++)
    {
        for (int y = 0; y < MAP_SIZE_Y; y++)
        {
            *(worldMap + x * MAP_SIZE_X + y) = pre_Map[x][y];
        }
    }
}

map::map()
{
    worldMap = (char*)calloc(MAP_SIZE_X * MAP_SIZE_Y, sizeof(char));
    char preMap[MAP_SIZE_X][MAP_SIZE_Y] =
    {
        {'#','#','#','#','#','#','#','#','#','#'},
        {'#','.','.','.','.','.','.','.','.','#'},
        {'#','.','.','.','.','.','.','.','.','#'},
        {'#','.','.','.','.','.','.','.','.','#'},
        {'#','#','#','#','#','#','#','.','.','#'},
        {'#','.','.','.','.','.','#','.','.','#'},
        {'#','.','.','.','.','.','.','.','.','#'},
        {'#','.','.','.','#','.','.','.','.','#'},
        {'#','.','.','.','#','.','.','.','.','#'},
        {'#','#','#','#','#','#','#','#','#','#'}
    };
    //����������� premap � map
    for (int x = 0; x < MAP_SIZE_X; x++)
    {
        for (int y = 0; y < MAP_SIZE_Y; y++)
        {
            *(worldMap + x * MAP_SIZE_X + y) = preMap[x][y];
        }
    }
}

map::~map()
{
}

int map::getWorldMap(char get_Map[MAP_SIZE_X][MAP_SIZE_Y])
{

        for (int x = 0; x < MAP_SIZE_X; x++)
        {
            for (int y = 0; y < MAP_SIZE_Y; y++)
            {
                get_Map[x][y] = *(worldMap + x * MAP_SIZE_X + y);
            }
        }

    return 0;
}