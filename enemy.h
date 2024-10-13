#pragma once
#include "entity.h"
#include "player.h"

class enemy : public entity
{
public:
    enemy(double x, double y, int hp, int dm, double sp);
    enemy();
    ~enemy();
    int enemyMovment(char* map, int Map_Size_X, player* pl);
    int playersVision(char* map, int Map_Size_X, player* pl);
};