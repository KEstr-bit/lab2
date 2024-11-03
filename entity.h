#pragma once
#include "helper.h"

class entity
{
protected:
    double coordX;             //координата по X
    double coordY;             //координата по Y
    int hitPoints;             //очки здоровья 
    int damage;                 //урон наносимый
    double speed;               //скорость 
public:
    entity(double coord_X, double coord_Y, double entity_Speed, int hit_Points, int entity_Damage);
    entity();
    ~entity();
    int getEntityCoord(double* coord_X, double* coord_Y);
    int getEntityCoord(int* coord_X, int* coord_Y);
    int getEntityDamage();
    int getEntityHitPoints();
    int attackEntity(int entity_Damage);
    int entityStep(СardinalDirections step_Direction);


};

