#pragma once
#include "weapon.h"

class shotGun : public weapon
{
private:
    //угол разброса
    static const int SPREAD_ANGLE = 30;
public:
    void shot(double coordX, double coordY, double shotAngle, std::map<int, entity*> &entiyes) override;
};