#pragma once
#include "weapon.h"
#include <vector>

class shotGun : public weapon
{
public:
    int shot(double coord_X, double coord_Y, �ardinalDirections shot_Direction, std::vector<bullet>& bullets) override;
};