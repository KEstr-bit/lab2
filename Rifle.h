#pragma once
#include "Gun.h"

class Rifle : public Gun
{
public:
    //переопределение выстрела
    Rifle(bool friendly);
    Rifle();
    bool shot(double coordX, double coordY, double shotAngle, std::vector<Entity*>& entiyes) override;
};
