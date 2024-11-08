#pragma once
#include "helper.h"
#include "GameMap.h"

class entity
{
protected:
    double coordX;             //координата по X
    double coordY;             //координата по Y
    int hitPoints;             //очки здоровья 
    int damage;                 //урон наносимый
    double speed;               //скорость 
    double viewAngle;          //угол обзора
public:
    entity(double coordX, double coordY, double speed, int hitPoints, int damage);
    entity();
    ~entity();
    int getEntityCoord(double* coordX, double* coordY);
    int getEntityCoord(int* coordX, int* coordY);
    int getEntityDamage();
    int getEntityHitPoints();
    double getEntityAngle();
    int attackEntity(int damage);
    int entityStep();
    int entityMapStep(GameMap* map);


};

