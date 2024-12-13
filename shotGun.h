#pragma once
#include "Gun.h"

class ShotGun final : public Gun
{
private:
    //угол разброса
    static const int SPREAD_ANGLE;
    static const double SIDE_SHIFT;
public:
    ShotGun(int magazineCapacity, int bulletCount, double bulletSpeed, double bulletDamage, TextureType bulletTexture, bool friendly);
    bool shot(double cordX, double cordY, double shotAngle, std::vector<Entity*>& entities) override;
};