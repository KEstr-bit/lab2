#pragma once
#include "entity.h"
#include "shotGun.h"
#include "avtomat.h"
#include "helper.h"
#include "GameMap.h"




class player : public entity
{
private:
    WeaponOption activeWeapon;

public:
    static const int VISION_SPEED = 1;
    static const int FOV = 60;
    shotGun* firstGun;                        //оружие игрока
    avtomat* secondGun;

public:
    player(double coordX, double coordY, double speed, int hitPoints, int damage);
    player();
    ~player();
    //перемщение игрока
    int playerMapStep(СardinalDirections step_Direction, GameMap* map);
    //получение координат игрока
    void changeVision(СardinalDirections direct_pl);
    int changeActiveWeapon();
    int shot(std::map<int, entity*> &entiyes);

    bool entityMovment(GameMap* map, double playerX, double playerY) override;
};
