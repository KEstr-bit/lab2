#pragma once
#include "weapon.h"

class avtomat : public weapon
{
public:
    //переопределение выстрела
    avtomat(bool friendly);
    avtomat();
    bool shot(double coordX, double coordY, double shotAngle, std::vector<Entity*>& entiyes) override;
};
