#pragma once
#include "TexturePack.h"
#include "GameMap.h"

class entity
{
protected:
    double coordX;             //координата по X
    double coordY;             //координата по Y
    int hitPoints;             //очки здоровья 
    int damage;                //урон наносимый
    double speed;              //скорость 
    double viewAngle;          //угол обзора
    double size;               //размер
    textureType texture;       //текстура 


public: 
    static int lastID;          //последний записанный id

    entity(double coordX, double coordY, double speed, int hitPoints, int damage, textureType texture);
    entity();
    ~entity();
    bool getEntityCoord(double* coordX, double* coordY);
    bool getEntityCoord(int* coordX, int* coordY);
    int getEntityDamage();
    int getEntityHitPoints();
    double getEntityAngle();
    double getSize();
    textureType getTextureType();

    //нанести урон объекту
    bool attackEntity(int damage);
    //движение вдоль направления взгляда
    bool entityStep();
    //движение с учетом стен
    void entityMapStep(GameMap* map);
    
    //виртуальная функция движения для наследников
    virtual bool entityMovment(GameMap* map, double playerX, double playerY) = 0;


};


