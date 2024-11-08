#pragma once
#include "entity.h"
#include "player.h"
#include "GameMap.h"

class enemy : public entity
{
public:
    static const double VISSION_STEP;

    enemy(double coordX, double coordY, double speed, int hitPoints, int damage);
    enemy();
    ~enemy();
    int enemyMovment(GameMap* map, double playerX, double playerY);
    bool playersVision(GameMap* map, double playerX, double playerY);
};