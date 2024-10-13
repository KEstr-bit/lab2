#pragma once
#include "entity.h"
#include "player.h"

class enemy : public entity
{
public:
    enemy(double coord_X, double coord_Y, double entity_Speed, int hit_Points, int entity_Damage);
    enemy();
    ~enemy();
    int enemyMovment(char* world_Map, int map_Size_X, player* pl);
    int playersVision(char* world_Map, int map_Size_X, player* pl);
};