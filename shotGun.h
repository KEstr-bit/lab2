#pragma once
#include "Gun.h"

class ShotGun final : public Gun
{
private:
    static const int MAX_SPREAD_ANGLE;
    static const double SIDE_SHIFT;
    int spreadAngle = MAX_SPREAD_ANGLE;

public:
    ShotGun(int magazineCapacity, int bulletCount, double bulletSpeed, 
        double bulletDamage,TextureType bulletTexture, bool friendly);

    bool shot(double cordX, double cordY, double shotAngle, 
        std::vector<Entity*>& entities) override;

    void reloading() override;
};