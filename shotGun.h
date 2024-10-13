#pragma once
#include "weapon.h"

class shotGun : public weapon
{
public:
    int shot(double coord_X, double coord_Y, ÑardinalDirections shot_Direction);
};