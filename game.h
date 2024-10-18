#pragma once
#include "player.h"
#include "enemy.h"
#include "map.h"

#define MAX_X 10
#define MAX_Y 10

class game
{
public:
    player* you;            //игрок
    enemy* monster;

public:
    game();
    ~game();

    //взаимодействие объектов
    int interaction(char world_Map[MAP_SIZE_X][MAP_SIZE_Y]);
    //вывод текущего состояния игры
    int vivod(char world_Map[MAP_SIZE_X][MAP_SIZE_Y]);
};