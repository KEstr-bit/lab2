#pragma once
#include "helper.h"

class entity
{
protected:
    double X_Coord;             //координата по X
    double Y_Coord;             //координата по Y
    int Hit_Points;             //очки здоровья 
    int Damage;                 //урон наносимый
    double speed;               //скорость 
public:
    entity(double x, double y, double sp, int hp, int dm);
    entity();
    ~entity();
    int getEntityCoord(double* x, double* y);
    int getEntityCoord(int* x, int* y);
    int getEntityDamage();
    int getEntityHitPoints();
    int attackEntity(int dm);
    int entityStep(СardinalDirections rotation);


};