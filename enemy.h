#pragma once
#include "Entity.h"
#include "Player.h"
#include "Rifle.h"
class Enemy : public Entity
{
protected:
    Entity* target;
public:
    static const double VISION_STEP; //шаг луча взгляда
    Enemy(double cordX, double cordY, double speed, double hitPoints, double damage, double size, TextureType texture, Entity* target);

protected:
    //обнаружение игрока
    bool isTargetSeen(GameMap& map);
    double updateAngle();
};


