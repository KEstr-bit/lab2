#pragma once
#include "weapon.h"

class shotGun : public weapon
{
private:
    //угол разброса
    static const int SPREAD_ANGLE = 30;
public:
    shotGun(bool f);
    shotGun();
    bool shot(double coordX, double coordY, double shotAngle, std::vector<Entity*>& entiyes) override;
};