#pragma once
#include <map>
#include "entity.h"

class weapon
{
protected:
    int bulletCount;                    //количество пуль, выпускаемых за раз
    double bulletSpeed;                 //скорость полета пули
    int bulletDamage;                   //урон, наносимы пулей

public:


public:
    virtual int shot(double coordX, double coordY, double shotAngle, std::map<int, entity*> &entiyes) = 0;
    weapon(int bulletCount, double bulletSpeed, int bulletDamage);
    weapon();
    ~weapon();

};