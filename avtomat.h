#pragma once
#include "weapon.h"

class avtomat : public weapon
{
public:
    int shot(double coordX, double coordY, double shotAngle, std::vector<bullet>& bullets) override;
};
