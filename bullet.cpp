#include "bullet.h"
#include "helper.h"

bullet::bullet(double coordX, double coordY, double flightAngle, int damage, double speed, textureType texture)
{
    this->coordX = coordX;
    this->coordY = coordY;
    this->speed = speed;
    this->damage = damage;
    this->texture = texture;
    viewAngle = flightAngle;
    remainLen = 10;
    size = 0.2;
}

bullet::bullet(double coordX, double coordY, double flightAngle, int damage, double speed)
{
    this->coordX = coordX;
    this->coordY = coordY;
    this->speed = speed;
    this->damage = damage;
    viewAngle = flightAngle;
    remainLen = 10;
    size = 0.2;
    texture = Bullet1;
}

bullet::bullet()
{
    coordX = -1;
    coordY = -1;
    speed = 0.2;
    damage = 50;
    viewAngle = 0;
    remainLen = 10;
    size = 0.2;
    texture = Bullet1;
}

bullet::~bullet()
{
}


bool bullet::entityMovment(GameMap* map, double playerX, double playerY)
{
    if (remainLen <= 0)
        return 1;

    this->entityStep();
    remainLen -= speed;

    if (map->isWall(coordX, coordY))
    {
        remainLen = 0;
    }
    
    return 0;
}