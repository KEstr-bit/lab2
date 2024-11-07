#include "bullet.h"
#include "helper.h"

bullet::bullet(double coord_X, double coord_Y, double flight_Angle, int entity_Damage, double entity_Speed)
{
    coordX = coord_X;
    coordY = coord_Y;
    flightAngle = flight_Angle;
    speed = entity_Speed;
    damage = entity_Damage;
}

bullet::bullet()
{
    coordX = -1;
    coordY = -1;
    flightAngle = 0;
    speed = 0.2;
    damage = 50;
}

bullet::~bullet()
{
}



double bullet::getBulletAngle()
{
    return flightAngle;
}


int bullet::bulletMovment()
{
    double deltaX = speed * cos(flightAngle * 3.14 / 180);
    double deltaY = speed * sin(flightAngle * 3.14 / 180);

    this->coordX += deltaX;
    this->coordY += deltaY;

    return 0;
}