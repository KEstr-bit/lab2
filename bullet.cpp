#include "bullet.h"
#include "helper.h"

bullet::bullet(double coord_X, double coord_Y, double final_coord_X, double final_coord_Y, int entity_Damage, double entity_Speed)
{
    coordX = coord_X;
    coordY = coord_Y;
    finalCoordX = final_coord_X;
    finalCoordY = final_coord_Y;
    speed = entity_Speed;
    damage = entity_Damage;
}

bullet::bullet()
{
    coordX = -1;
    coordY = -1;
    finalCoordX = -1;
    finalCoordY = -1;
    speed = 0.2;
    damage = 50;
}

bullet::~bullet()
{
}



int bullet::getBulletCoords(double* final_coord_X, double* final_coord_Y)
{
    *final_coord_X = finalCoordX;
    *final_coord_Y = finalCoordY;
    return 0;
}

int bullet::getBulletCoords(int* final_coord_X, int* final_coord_Y)
{
    *final_coord_X = roundd(finalCoordX);
    *final_coord_Y = roundd(finalCoordY);
    return 0;
}

int bullet::bulletMovment()
{
    double deltaX = finalCoordX - coordX;
    double deltaY = finalCoordY - coordY;

    //движение пули к конечной точке
    if (abss(deltaX) > abss(deltaY))
    {
        if (deltaX < 0)
            this->entityStep(North);
        else
            this->entityStep(South);

    }
    else
    {
        if (deltaY > 0)
            this->entityStep(East);
        else
            this->entityStep(West);
    }

    return 0;
}