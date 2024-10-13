#include "entity.h"
#include "helper.h"

entity::entity(double x, double y, double sp, int hp, int dm)
{
    Damage = dm;
    Hit_Points = hp;
    X_Coord = x;
    Y_Coord = y;
    speed = sp;

}

entity::entity()
{
    X_Coord = 8;
    Y_Coord = 1;
    Hit_Points = 100;
    speed = 1;
    Damage = 50;
}

entity::~entity()
{
}

int entity::getEntityCoord(double* x, double* y)
{
    *x = X_Coord;
    *y = Y_Coord;
    return 0;
}

int entity::getEntityDamage()
{
    return Damage;
}

int entity::getEntityHitPoints()
{
    return Hit_Points;
}

int entity::attackEntity(int dm)
{
    Hit_Points -= dm;
    return 0;
}

int entity::entityStep(ÑardinalDirections rotation)
{
    int i = 0;
    switch (rotation)
    {
    case 0: X_Coord -= speed; break;
    case 1: Y_Coord += speed; break;
    case 2: X_Coord += speed; break;
    case 3: Y_Coord -= speed; break;
    default: i = 1;
    }

    return i;

}

int entity::getEntityCoord(int* x, int* y)
{
    *x = roundd(X_Coord);
    *y = roundd(Y_Coord);
    return 0;
}