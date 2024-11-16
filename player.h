#pragma once
#include "entity.h"
#include "shotGun.h"
#include "avtomat.h"
#include "helper.h"

class player : public entity
{
private:
    WeaponOption activeWeapon;  //активное оружие

public:
    static const int VISION_SPEED = 1;  //скорость изменения угла обзора
    static const int FOV = 60;          //ширина обзора
    shotGun* firstGun;                  //оружие игрока1
    avtomat* secondGun;                 //оружие игрока2

public:
    player(double coordX, double coordY, double speed, int hitPoints, int damage);
    player();
    ~player();
    //перемщение игрока
    bool playerMapStep(СardinalDirections step_Direction, GameMap* map);
    //поворот угла обзора
    void changeVision(СardinalDirections direct_pl);
    //смена оружия
    int changeActiveWeapon();
    //выстрел 
    int shot(std::map<int, entity*> &entiyes);

    bool entityMovment(GameMap* map, double playerX, double playerY) override;
};
