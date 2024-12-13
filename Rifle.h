#pragma once
#include "Gun.h"

class Rifle final : public Gun
{
public:
    static const double SIDE_SHIFT;
public:
    //переопределение выстрела
    Rifle(int magazineCapacity, int bulletCount, double bulletSpeed, double bulletDamage, TextureType bulletTexture, bool friendly);
    bool shot(double cordX, double cordY, double shotAngle, std::vector<Entity*>& entities) override;
};
