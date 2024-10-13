#pragma once
#include "entity.h"
#include "shotGun.h"
#include "helper.h"

class player : public entity
{
private:
    ÑardinalDirections playerRotation;

public:
    shotGun* gun;                        //îğóæèå èãğîêà

public:
    player(double x, double y, double sp, int hp, int dm, ÑardinalDirections rotation);
    player();
    ~player();
    //ïåğåìùåíèå èãğîêà
    int playerStep(ÑardinalDirections rotation);
    //ïîëó÷åíèå êîîğäèíàò èãğîêà
    ÑardinalDirections getPlayerRotation();

    int gamePlayerStep(char* map, int Map_Size_X, ÑardinalDirections rot);

};
