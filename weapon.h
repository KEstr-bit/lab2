#pragma once
#include "bullet.h"
#include "helper.h"

class weapon
{
protected:
    int bulletCount;                    //количество пуль, выпускаемых за раз
    double speed;                       //скорость полета пули
    int damage;                         //урон, наносимы пулей
    int activeBullets[10];              //список, существующих пуль
    int countActiveBullets;
public:
    bullet* bulls[MAX_BULLETS];         //массив пуль

public:
    weapon(int bc, double sp, int dm);
    weapon();
    ~weapon();
    //получит характеристики оружия
    int getWeaponCountBullets();
    int setActiveBullet(int index, int active);
    int getActiveBullet(int index);
    int changeCountActiveBullets(int change);
    int allBulletMovment();

};