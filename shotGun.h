#pragma once
#include "Gun.h"

class ShotGun : public Gun
{
private:
    //угол разброса
    static const int SPREAD_ANGLE = 30;
public:
    ShotGun(bool f);
    ShotGun();
    bool shot(double coordX, double coordY, double shotAngle, std::vector<Entity*>& entiyes) override;
};