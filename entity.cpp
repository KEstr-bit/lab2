#include "entity.h"
#include "helper.h"

entity::entity(double coordX, double coordY, double speed, int hitPoints, int damage, textureType texture)
{
    this->damage = damage;
    this->hitPoints = hitPoints;
    this->coordX = coordX;
    this->coordY = coordY;
    this->speed = speed;
    this->texture = texture;
    viewAngle = 0;
    lastID++;
    size = 1;
}

entity::entity()
{
    coordX = 8;
    coordY = 1;
    hitPoints = 100;
    speed = 1;
    damage = 50;
    viewAngle = 0;
    lastID++;
    size = 1;
    texture = Enemy1;
}

entity::~entity()
{
}

int entity::getEntityCoord(double* coordX, double* coordY)
{
    *coordX = this->coordX;
    *coordY = this->coordY;
    return 0;
}

int entity::getEntityDamage()
{
    return damage;
}

int entity::getEntityHitPoints()
{
    return hitPoints;
}

double entity::getEntityAngle()
{
    return viewAngle;
}

int entity::attackEntity(int damage)
{
    if (hitPoints > 0)
    {
        hitPoints -= damage;
        return 0;
    }
    else
        return 1;
}

int entity::entityStep()
{
    if (hitPoints > 0)
    {
        coordX += projectionToX(speed, degToRad(viewAngle));
        coordY += projectionToY(speed, degToRad(viewAngle));
        return 0;
    }
    return 1;
}

int entity::entityMapStep(GameMap* map)
{
    double oldX, oldY;
    this->getEntityCoord(&oldX, &oldY);

    this->entityStep();

    //если объект шагнул в стену
    if (map->isWall(this->coordX, this->coordY))
    {
        double deltaX = this->coordX - oldX;
        double deltaY = this->coordY - oldY;

        //если можно продолжить движение по оси X
        if (!map->isWall(oldX + deltaX, oldY))
        {
            this->coordX = oldX + deltaX;
            this->coordY = oldY;
        }
        //если можно продолжить движение по оси Y
        else if (!map->isWall(oldX, oldY + deltaY))
        {
            this->coordX = oldX;
            this->coordY = oldY + deltaY;
        }
        else
        {
            this->coordX = oldX;
            this->coordY = oldY;
        }
    }
    return 0;
}

int entity::getEntityCoord(int* coordX, int* coordY)
{
    if (hitPoints > 0)
    {
        *coordX = myRound(this->coordX);
        *coordY = myRound(this->coordY);
        return 0;
    }
    return 1;
}

double entity::getSize()
{
    return size;
}

textureType entity::getTextureType()
{
    return texture;
}
