#pragma once
#include <map>
#include "Entity.h"

class Gun
{
public:
    const int magazineCapacity;
    textureType texture;
protected:
    int bulletCount;                    //количество пуль, выпускаемых за раз
    double bulletSpeed;                 //скорость полета пули
    int bulletDamage;                   //урон, наносимы пулей
    bool friendly;
    int ammunition = magazineCapacity;
    bool eventFl = true;
    float textureX = 0;
    float textureY = 3;

public:
    Gun(int bulletCount, double bulletSpeed, int bulletDamage, bool friendly);
    Gun();
    Gun(bool friendly);
    virtual ~Gun();
    void setAnimation(int animation)
    {
        textureX = 0;
        textureY = animation;
        eventFl = true;
    }
    //выстрел из оружия
    virtual bool shot(double coordX, double coordY, double shotAngle, std::vector<Entity*>& entiyes) = 0;
    void update();
    float getTextureX()
    {
        return textureX;
    }

    float getTextureY()
    {
        return textureY;
    }

    void reloading()
    {
        setAnimation(2);
        ammunition = magazineCapacity;
    }

};