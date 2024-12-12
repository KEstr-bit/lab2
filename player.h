#pragma once
#include "entity.h"
#include "shotGun.h"
#include "avtomat.h"
#include "helper.h"

class Player : public Entity
{
private:
    WeaponOption activeWeapon;  //активное оружие

public:
    static const int VISION_SPEED = 1;  //скорость изменения угла обзора
    static const int FOV = 60;          //ширина обзора
    shotGun* firstGun;                  //оружие игрока1
    avtomat* secondGun;                 //оружие игрока2

public:
    Player(double coordX, double coordY, double speed, int hitPoints, int damage);
    Player();
    ~Player();
    //перемщение игрока
    void playerMapStep(СardinalDirections step_Direction, GameMap* map);
    //поворот угла обзора
    void changeVision(double angle);
    //смена оружия
    void changeActiveWeapon();
    //выстрел 
    void shot(std::vector<Entity*>& entiyes);
    weapon* getActiveWeapon();

    bool update(GameMap* map, std::vector<Entity*>& entities) override;
};
