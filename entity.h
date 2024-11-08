#pragma once
#include "helper.h"
#include "GameMap.h"

class entity
{
protected:
    double coordX;             //���������� �� X
    double coordY;             //���������� �� Y
    int hitPoints;             //���� �������� 
    int damage;                 //���� ���������
    double speed;               //�������� 
    double viewAngle;          //���� ������
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

