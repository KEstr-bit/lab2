#pragma once
#include "entity.h"
#include "player.h"

class enemy : public entity
{
public:
    enemy(double coord_X, double coord_Y, double entity_Speed, int hit_Points, int entity_Damage);
    enemy();
    ~enemy();
    int enemyMovment(char* world_Map, int map_Size_X, double player_X, double player_Y);
    int playersVision(char* world_Map, int map_Size_X, double player_X, double player_Y);
};