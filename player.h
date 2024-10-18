#pragma once
#include "entity.h"
#include "shotGun.h"
#include "avtomat.h"
#include "helper.h"
#include "map.h"

class player : public entity
{
private:
    ÑardinalDirections playerDirection;
    WeaponOption activeWeapon;

public:
    shotGun* firstGun;                        //îğóæèå èãğîêà
    avtomat* secondGun;

public:
    player(double coord_X, double coord_Y, double entity_Speed, int hit_Points, int entity_Damage, ÑardinalDirections direction);
    player();
    ~player();
    //ïåğåìùåíèå èãğîêà
    int playerStep(ÑardinalDirections step_Direction);
    //ïîëó÷åíèå êîîğäèíàò èãğîêà
    ÑardinalDirections getPlayerDirection();

    int gamePlayerStep(char* world_Map, ÑardinalDirections step_Direction);
    int changeActiveWeapon();
    int shot();
};
