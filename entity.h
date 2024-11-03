#pragma once
#include "helper.h"

class entity
{
protected:
    double coordX;             //���������� �� X
    double coordY;             //���������� �� Y
    int hitPoints;             //���� �������� 
    int damage;                 //���� ���������
    double speed;               //�������� 
public:
    entity(double coord_X, double coord_Y, double entity_Speed, int hit_Points, int entity_Damage);
    entity();
    ~entity();
    int getEntityCoord(double* coord_X, double* coord_Y);
    int getEntityCoord(int* coord_X, int* coord_Y);
    int getEntityDamage();
    int getEntityHitPoints();
    int attackEntity(int entity_Damage);
    int entityStep(�ardinalDirections step_Direction);


};

