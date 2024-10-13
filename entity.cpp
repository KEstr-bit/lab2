#include "entity.h"

entity::entity(double coord_X, double coord_Y, double entity_Speed, int hit_Points, int entity_Damage)
{
    damage = entity_Damage;
    hitPoints = hit_Points;
    coordX = coord_X;
    coordY = coord_Y;
    speed = entity_Speed;

}

entity::entity()
{
    coordX = 8;
    coordY = 1;
    hitPoints = 100;
    speed = 1;
    damage = 50;
}

entity::~entity()
{
}

int entity::getEntityCoord(double* coord_X, double* coord_Y)
{
    *coord_X = coordX;
    *coord_Y = coordY;
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

int entity::attackEntity(int entity_Damage)
{
    if (hitPoints > 0)
    {
        hitPoints -= entity_Damage;
        return 0;
    }
    else
        return 1;
}

int entity::entityStep(ÑardinalDirections step_Direction)
{
    if (hitPoints > 0)
    {
        int i = 0;
        switch (step_Direction)
        {
        case North: coordX -= speed; break;
        case East: coordY += speed; break;
        case South: coordX += speed; break;
        case West: coordY -= speed; break;
        default: i = 1;
        }

        return i;
    }
    return 2;
}

int entity::getEntityCoord(int* coord_X, int* coord_Y)
{
    if (hitPoints > 0)
    {
        *coord_X = roundd(coordX);
        *coord_Y = roundd(coordY);
        return 0;
    }
    return 1;
}