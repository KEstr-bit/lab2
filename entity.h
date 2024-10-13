#pragma once
#include "helper.h"

class entity
{
protected:
    double X_Coord;             //���������� �� X
    double Y_Coord;             //���������� �� Y
    int Hit_Points;             //���� �������� 
    int Damage;                 //���� ���������
    double speed;               //�������� 
public:
    entity(double x, double y, double sp, int hp, int dm);
    entity();
    ~entity();
    int getEntityCoord(double* x, double* y);
    int getEntityCoord(int* x, int* y);
    int getEntityDamage();
    int getEntityHitPoints();
    int attackEntity(int dm);
    int entityStep(�ardinalDirections rotation);


};