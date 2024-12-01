#pragma once
#include "TexturePack.h"
#include "GameMap.h"
#include "helper.h"

class Entity
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
    int textureX;
    int textureY;
    bool eventFl = false;
public: 
    static int lastID;          //последний записанный id

    Entity(double coordX, double coordY, double speed, int hitPoints, int damage, textureType texture);
    Entity();
    ~Entity();
    bool getEntityCoord(double* coordX, double* coordY);
    bool getEntityCoord(int* coordX, int* coordY);
    int getEntityDamage();
    int getEntityHitPoints();
    double getEntityAngle();
    double getSize();
    textureType getTextureType();
    int getTextureX();
    int getTextureY();
    //нанести урон объекту
    void attackEntity(int damage);
    //движение вдоль направления взгляда
    bool isAlive();
    bool entityStep();
    //движение с учетом стен
    void entityMapStep(GameMap* map);
    
    //виртуальная функция движения для наследников
    virtual bool entityMovment(GameMap* map, std::map<int, Entity*>& entities) = 0;


    bool intersects(Entity* other) const {
        double dist = helper::calcDistance(coordX, coordY, other->coordX, other->coordY);
        return dist < (size + other->size * 0.7) / 2;
    }


};


