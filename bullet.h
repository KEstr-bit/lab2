#pragma once
#include "entity.h"

class bullet : public entity
{
public:
    bullet(double X_Crd, double Y_Crd, double fX_Crd, double fY_Crd, int dm, double sp);
    bullet();
    ~bullet();
    //получение координат точки назначения пули
    int getBulletCoords(double* fin_x, double* fin_y);
    int getBulletCoords(int* fin_x, int* fin_y);
    //движение пули
    int bulletMovment();

private:
    double fin_X_Coord; //конечная координата пули по X
    double fin_Y_Coord; //конечная координата пул по Y
};