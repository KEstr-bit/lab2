#pragma once
#include "bullet.h"
#include "helper.h"
#include <vector>

class weapon
{
protected:
    int bulletCount;                    //количество пуль, выпускаемых за раз
    double bulletSpeed;                 //скорость полета пули
    int bulletDamage;                   //урон, наносимы пулей

public:


public:
    virtual int shot(double coordX, double coordY, double shotAngle, std::vector<bullet>& bullets) = 0;
    weapon(int bulletCount, double bulletSpeed, int bulletDamage);
    weapon();
    ~weapon();

};