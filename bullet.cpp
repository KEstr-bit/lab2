#include "bullet.h"

bullet::bullet(bullet* b)
{
    this->cordX = b->cordX;
    this->cordY = b->cordY;
    this->speed = b->speed;
    this->damage = b->damage;
    this->texture = b->texture;
    this->viewAngle = b->viewAngle;
    this->hitPoints = b->hitPoints;
    this->size = b->size;
    hitPoints = 1;
    textureY = 2;
}

bullet::bullet(double coordX, double coordY, double flightAngle, int damage, double speed, textureType texture)
{
    this->cordX = coordX;
    this->cordY = coordY;
    this->speed = speed;
    this->damage = damage;
    this->texture = texture;
    viewAngle = flightAngle;
    hitPoints = 10;
    size = 0.25;
    textureY = 2;
}

bullet::bullet(double coordX, double coordY, double flightAngle, int damage, double speed)
{
    this->cordX = coordX;
    this->cordY = coordY;
    this->speed = speed;
    this->damage = damage;
    viewAngle = flightAngle;
    hitPoints = 10;
    size = 0.25;
    texture = Bullet1;
    textureY = 2;
}

bullet::bullet(double coordX, double coordY, double flightAngle, int damage, double speed, bool friendly)
{
    this->cordX = coordX;
    this->cordY = coordY;
    this->speed = speed;
    this->damage = damage;
    this->friendly = friendly;
    viewAngle = flightAngle;
    hitPoints = 10;
    size = 0.25;
    texture = Bullet1;
    textureY = 2;
}

bullet::bullet()
{
    cordX = 8;
    cordY = 1;
    speed = 0.2;
    damage = 50;
    viewAngle = 90;
    hitPoints = 10;
    size = 0.25;
    texture = Bullet1;
    textureY = 2;
}

bullet::~bullet()
{
}


bool bullet::update(GameMap* map, std::vector<Entity*>& entities)
{
    frameShift();

    if (eventFl)
        return false;

    if (!this->isAlive())
        return true;

    //уменьшение оставшегося пути при успешном движении
    if(!this->entityStep())
        hitPoints -= speed;

    //если пуля врезалась в стену
    if (map->isWall(cordX, cordY))
    {
        this->setRemLen(0);
    }
    return false;
}

void bullet::setRemLen(double len) {
    hitPoints = len;
    if (!this->isAlive() && !eventFl)
    {
        textureY = 1;
        textureX = 0;
        eventFl = true;
    }
}

