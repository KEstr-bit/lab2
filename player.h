#pragma once
#include "entity.h"
#include "shotGun.h"
#include "helper.h"

class player : public entity
{
private:
    �ardinalDirections playerRotation;

public:
    shotGun* gun;                        //������ ������

public:
    player(double x, double y, double sp, int hp, int dm, �ardinalDirections rotation);
    player();
    ~player();
    //���������� ������
    int playerStep(�ardinalDirections rotation);
    //��������� ��������� ������
    int getPlayerRotation();

};
