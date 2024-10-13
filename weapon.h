#pragma once
#include "bullet.h"
#include "helper.h"

class weapon
{
protected:
    int bulletCount;                    //количество пуль, выпускаемых за раз
    double bulletSpeed;                       //скорость полета пули
    int bulletDamage;                         //урон, наносимы пулей
    int activeBullets[10];              //список, существующих пуль
    int countActiveBullets;
public:
    bullet* bullets[MAX_BULLETS];         //массив пуль

public:
    weapon(int bullet_Count, double bullet_Speed, int bullet_Damage);
    weapon();
    ~weapon();
    //получит характеристики оружия
    int getCountActiveBullets();
    int setActiveBullet(int index, int active);
    int getActiveBullet(int index);
    int changeCountActiveBullets(int change);
    int allBulletMovment();

};