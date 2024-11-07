#pragma once
#include "entity.h"

class bullet : public entity
{
public:
    bullet(double coord_X, double coord_Y, double flight_Angle, int entity_Damage, double entity_Speed);
    bullet();
    ~bullet();
    //��������� ��������� ����� ���������� ����
    double getBulletAngle();
    //�������� ����
    int bulletMovment();

private:
    double flightAngle;
};