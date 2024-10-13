#pragma once
#include "weapon.h"

class shotGun : public weapon
{
public:
    int Shot(double X_coord, double Y_coord, int rotation);
};