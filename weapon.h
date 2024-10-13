#pragma once
#include "bullet.h"
#include "helper.h"

class weapon
{
protected:
    int bulletCount;    //количество пуль, выпускаемых за раз
    double speed;       //скорость полета пули
    int damage;         //урон, наносимы пулей
    int type;           //тип оружия: 0 - дробовик, 1 - автомат
    int activeBullets[10];              //список, существующих пуль
    СardinalDirections playerRotation;  //направление взгляда игрока
    int countActiveBullets;
public:
    bullet* bulls[MAX_BULLETS];         //массив пуль

public:
    weapon(int bc, double sp, int tp, int dm);
    weapon();
    ~weapon();
    //получит характеристики оружия
    int getWeaponStat(int* bc, double* sp, int* dm, int* t);
    int getWeaponCountBullets();
    int setActiveBullet(int index, int active);
    int getActiveBullet(int index);
    int changeCountActiveBullets(int change);
    int allBulletMovment();

};