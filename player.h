#pragma once
#include "entity.h"
#include "shotGun.h"
#include "helper.h"

class player : public entity
{
public:
    player(double x, double y, double sp, int hp, int dm, СardinalDirections rotation);
    player();
    ~player();
    //перемщение игрока
    int playerStep(СardinalDirections rotation);
    //получение координат игрока
    int getPlayerRotation();



private:
    СardinalDirections playerRotation;
public:
    shotGun* gun;                        //оружие игрока

};
