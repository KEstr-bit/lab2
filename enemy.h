#pragma once
#include "Entity.h"
#include "Player.h"
#include "Rifle.h"
class Enemy : public Entity
{
protected:
    Player* player;
public:
    static const double VISION_STEP; //шаг луча взгляда

    Enemy(double coordX, double coordY, double speed, int hitPoints, int damage, Player* player);
    Enemy(Player* player);
    Enemy();
    ~Enemy();

    //движение врага
    bool update(GameMap* map, std::vector<Entity*>& entities) override;

    //обнаружение игрока
    bool playersVision(GameMap* map);
};


