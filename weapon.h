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
    virtual int shot(double coord_X, double coord_Y, double shot_corner, std::vector<bullet>& bullets) = 0;
    weapon(int bullet_Count, double bullet_Speed, int bullet_Damage);
    weapon();
    ~weapon();

};