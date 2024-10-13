#include "bullet.h"
#include "helper.h"

bullet::bullet(double X_Crd, double Y_Crd, double fX_Crd, double fY_Crd, int dm, double sp)
{
    X_Coord = X_Crd;
    Y_Coord = Y_Crd;
    fin_X_Coord = fX_Crd;
    fin_Y_Coord = fY_Crd;
    speed = sp;
    Damage = dm;
}

bullet::bullet()
{
    X_Coord = -1;
    Y_Coord = -1;
    fin_X_Coord = -1;
    fin_Y_Coord = -1;
    speed = 0.2;
    Damage = 50;
}

bullet::~bullet()
{
}



int bullet::getBulletCoords(double* bullet_fin_x, double* bullet_fin_y)
{
    *bullet_fin_x = fin_X_Coord;
    *bullet_fin_y = fin_Y_Coord;
    return 0;
}

int bullet::getBulletCoords(int* bullet_fin_x, int* bullet_fin_y)
{
    *bullet_fin_x = roundd(fin_X_Coord);
    *bullet_fin_y = roundd(fin_Y_Coord);
    return 0;
}

int bullet::bulletMovment()
{
    //движение пули к конечной точке
    if (abss(fin_X_Coord - X_Coord) > abss(fin_Y_Coord - Y_Coord))
    {
        if (fin_X_Coord < X_Coord)
            this->entityStep(North);
        else
            if (fin_X_Coord > X_Coord)
                this->entityStep(South);

    }
    else
    {
        if (fin_Y_Coord > Y_Coord)
            this->entityStep(East);
        else
            if (fin_Y_Coord < Y_Coord)
                this->entityStep(West);
    }

    return 0;
}