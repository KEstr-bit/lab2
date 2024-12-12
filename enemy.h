#pragma once
#include "entity.h"
#include "player.h"
#include "avtomat.h"
class enemy : public Entity
{
protected:
    Player* player;
public:
    static const double VISION_STEP; //шаг луча взгляда

    enemy(double coordX, double coordY, double speed, int hitPoints, int damage, Player* player);
    enemy(Player* player);
    enemy();
    ~enemy();

    //движение врага
    bool update(GameMap* map, std::vector<Entity*>& entities) override;

    //обнаружение игрока
    bool playersVision(GameMap* map);
};


