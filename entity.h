#pragma once
#include "TexturePack.h"
#include "GameMap.h"

class entity
{
protected:
    double coordX;             //���������� �� X
    double coordY;             //���������� �� Y
    int hitPoints;             //���� �������� 
    int damage;                //���� ���������
    double speed;              //�������� 
    double viewAngle;          //���� ������
    double size;               //������
    textureType texture;       //�������� 


public: 
    static int lastID;          //��������� ���������� id

    entity(double coordX, double coordY, double speed, int hitPoints, int damage, textureType texture);
    entity();
    ~entity();
    int getEntityCoord(double* coordX, double* coordY);
    int getEntityCoord(int* coordX, int* coordY);
    int getEntityDamage();
    int getEntityHitPoints();
    double getEntityAngle();
    double getSize();
    textureType getTextureType();

    //������� ���� �������
    int attackEntity(int damage);

    //�������� ����� ����������� �������
    int entityStep();
    //�������� � ������ ����
    int entityMapStep(GameMap* map);
    
    //����������� ������� �������� ��� �����������
    virtual bool entityMovment(GameMap* map, double playerX, double playerY) = 0;


};


