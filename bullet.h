#pragma once
#include "entity.h"

class bullet : public entity
{
public:
    bullet(double X_Crd, double Y_Crd, double fX_Crd, double fY_Crd, int dm, double sp);
    bullet();
    ~bullet();
    //��������� ��������� ����� ���������� ����
    int getBulletCoords(double* fin_x, double* fin_y);
    int getBulletCoords(int* fin_x, int* fin_y);
    //�������� ����
    int bulletMovment();

private:
    double fin_X_Coord; //�������� ���������� ���� �� X
    double fin_Y_Coord; //�������� ���������� ��� �� Y
};