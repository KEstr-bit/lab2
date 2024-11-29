#include "entity.h"
#include "helper.h"

Entity::Entity(double coordX, double coordY, double speed, int hitPoints, int damage, textureType texture)
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

Entity::Entity()
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

Entity::~Entity()
{
}

bool Entity::getEntityCoord(double* coordX, double* coordY)
{
    *coordX = this->coordX;
    *coordY = this->coordY;
    return hitPoints <= 0;
}

bool Entity::getEntityCoord(int* coordX, int* coordY)
{
    *coordX = helper::myRound(this->coordX);
    *coordY = helper::myRound(this->coordY);
    return hitPoints <= 0;
}

int Entity::getEntityDamage()
{
    return damage;
}

int Entity::getEntityHitPoints()
{
    return hitPoints;
}

double Entity::getEntityAngle()
{
    return viewAngle;
}

bool Entity::attackEntity(int damage)
{
    if (hitPoints > 0)
    {
        hitPoints -= damage;
        return false;
    }
    else
        return true;
}

bool Entity::entityStep()
{
    coordX += helper::projectionToX(speed, helper::degToRad(viewAngle));
    coordY += helper::projectionToY(speed, helper::degToRad(viewAngle));
    return hitPoints <= 0;
}

void Entity::entityMapStep(GameMap* map)
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
}



double Entity::getSize()
{
    return size;
}

textureType Entity::getTextureType()
{
    return texture;
}
