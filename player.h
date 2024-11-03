#pragma once
#include "entity.h"
#include "shotGun.h"
#include "avtomat.h"
#include "helper.h"
#include "map.h"




class player : public entity
{
private:
    �ardinalDirections playerDirection;
    WeaponOption activeWeapon;
public:
    double visionCorner;
    const double VISION_SPEED = 1;
    const int FOV = 60;

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

    void changeVision(�ardinalDirections direct_pl);
    int gamePlayerStep(char* world_Map, �ardinalDirections step_Direction);
    int changeActiveWeapon();
    int shot(std::vector<bullet>& bullets);
};
