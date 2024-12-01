#pragma once
#include "entity.h"
#include "player.h"
#include "avtomat.h"
class enemy : public Entity
{
private:
    avtomat* avt;
    Player* player;
public:
    static const double VISSION_STEP; //шаг луча взгляда

    enemy(double coordX, double coordY, double speed, int hitPoints, int damage, Player* player);
    enemy(Player* player);
    ~enemy();

    //движение врага
    bool entityMovment(GameMap* map, std::map<int, Entity*>& entities) override;

    //обнаружение игрока
    bool playersVision(GameMap* map);
};