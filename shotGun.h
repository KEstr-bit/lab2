#pragma once
#include "weapon.h"
#include <vector>

class shotGun : public weapon
{
public:
    int shot(double coord_X, double coord_Y, double shot_corner, std::vector<bullet>& bullets) override;
};