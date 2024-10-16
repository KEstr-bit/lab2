#pragma once
#include "entity.h"
#include "shotGun.h"
#include "avtomat.h"
#include "helper.h"

class player : public entity
{
private:
    �ardinalDirections playerDirection;
    WeaponOption activeWeapon;

public:
    shotGun* firstGun;                        //������ ������
    avtomat* secondGun;

public:
    player(double coord_X, double coord_Y, double entity_Speed, int hit_Points, int entity_Damage, �ardinalDirections direction);
    player();
    ~player();
    //���������� ������
    int playerStep(�ardinalDirections step_Direction);
    //��������� ��������� ������
    �ardinalDirections getPlayerDirection();

    int gamePlayerStep(char* world_Map, int map_Size_X, �ardinalDirections step_Direction);
    int changeActiveWeapon();
    int shot();
};
