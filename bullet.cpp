#include "bullet.h"

bullet::bullet(bullet* b)
{
    this->coordX = b->coordX;
    this->coordY = b->coordY;
    this->speed = b->speed;
    this->damage = b->damage;
    this->texture = b->texture;
    this->viewAngle = b->viewAngle;
    this->remainLen = b->remainLen;
    this->size = b->size;
}

bullet::bullet(double coordX, double coordY, double flightAngle, int damage, double speed, textureType texture)
{
    this->coordX = coordX;
    this->coordY = coordY;
    this->speed = speed;
    this->damage = damage;
    this->texture = texture;
    viewAngle = flightAngle;
    remainLen = 10;
    size = 0.5;
}

bullet::bullet(double coordX, double coordY, double flightAngle, int damage, double speed)
{
    this->coordX = coordX;
    this->coordY = coordY;
    this->speed = speed;
    this->damage = damage;
    viewAngle = flightAngle;
    remainLen = 10;
    size = 0.5;
    texture = Bullet1;
}

bullet::bullet()
{
    coordX = 8;
    coordY = 1;
    speed = 0.2;
    damage = 50;
    viewAngle = 90;
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
        return true;

    //уменьшение оставшегося пути при успешном движении
    if(!this->entityStep())
        remainLen -= speed;

    //если пуля врезалась в стену
    if (map->isWall(coordX, coordY))
    {
        remainLen = 0;
    }
    
    return false;
}

void bullet::setRemLen(double len) {
    remainLen = len;
}