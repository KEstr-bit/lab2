#pragma once
#include "entity.h"

class enemy : public Entity
{
public:
    static const double VISSION_STEP; //шаг луча взгляда

    enemy(double coordX, double coordY, double speed, int hitPoints, int damage);
    enemy();
    ~enemy();

    //движение врага
    bool entityMovment(GameMap* map, double playerX, double playerY) override;

    //обнаружение игрока
    bool playersVision(GameMap* map, double playerX, double playerY);
};