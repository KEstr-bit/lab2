#pragma once
#include "entity.h"

class bullet : public entity
{
public:
    bullet(double coord_X, double coord_Y, double final_coord_X, double final_coord_Y, int entity_Damage, double entity_Speed);
    bullet();
    ~bullet();
    //��������� ��������� ����� ���������� ����
    int getBulletCoords(double* final_coord_X, double* final_coord_Y);
    int getBulletCoords(int* final_coord_X, int* final_coord_Y);
    //�������� ����
    int bulletMovment();

private:
    double finalCoordX; //�������� ���������� ���� �� X
    double finalCoordY; //�������� ���������� ��� �� Y
};