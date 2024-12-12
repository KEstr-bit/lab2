#pragma once
#include "Entity.h"
#include "ShotGun.h"
#include "Rifle.h"
#include "Helper.h"

class Player : public Entity
{
private:
    GunOption activeWeapon;  //активное оружие

public:
    static const int VISION_SPEED = 1;  //скорость изменения угла обзора
    static const int FOV = 60;          //ширина обзора
    ShotGun* firstGun;                  //оружие игрока1
    Rifle* secondGun;                 //оружие игрока2

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
    Gun* getActiveWeapon();

    bool update(GameMap* map, std::vector<Entity*>& entities) override;
};
