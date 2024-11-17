#pragma once
#include "weapon.h"

class avtomat : public weapon
{
public:
    //переопределение выстрела
    void shot(double coordX, double coordY, double shotAngle, std::map<int, entity*> &entiyes) override;
};
