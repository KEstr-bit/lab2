#pragma once
#include "Entity.h"
#include "ShotGun.h"
#include "Rifle.h"
#include "Helper.h"

class Player final : public Entity
{
private:
    GunOption activeWeapon;             //активное оружие
    ShotGun* firstGun;                  //оружие игрока1
    Rifle* secondGun;                   //оружие игрока2

public:
    static const int VISION_SPEED = 1;  //скорость изменения угла обзора
    static const int FOV = 60;          //ширина обзора

public:
    Player(double cordX, double cordY);
    ~Player();
    Gun* getActiveWeapon() const;

    void playerMapStep(CardinalDirections stepDirection, GameMap& map); //перемщение игрока
    void changeVision(double angle);    //поворот угла обзора
    void changeActiveWeapon();          //смена оружия
    void shot(std::vector<Entity*>& entities) const;   //выстрел 

    bool update(GameMap& map, std::vector<Entity*>& entities) override;
};
