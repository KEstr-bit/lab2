#include "ShotGun.h"
#include "Helper.h"
#include "Bullet.h"

ShotGun::ShotGun(bool friendly)
{
    this->friendly = friendly;
    this->bulletCount = 3;
    texture = SHOTGUN;
}

ShotGun::ShotGun()
{
    this->bulletCount = 3;
    texture = SHOTGUN;
}

bool ShotGun::shot(double coordX, double coordY, double shotAngle, std::vector<Entity*>& entiyes)
{
    //смещение угла полета
    if(ammunition < bulletCount)
        return false;

    if (eventFl)
        return true;

    ammunition -= bulletCount;

    eventFl = true;
    textureX = 0;
    textureY = 1;

    //смещение угла полета
    double sideShift = 0;
    if (bulletCount > 1)
    {
        sideShift = SPREAD_ANGLE / (bulletCount - 1);
        shotAngle -= SPREAD_ANGLE / 2;
    }

    

    for (int i = 0; i < bulletCount; i++)
    {
        double x, y;
        x = Helper::projectionToX(10*bulletSpeed, Helper::degToRad(shotAngle));
        y = Helper::projectionToY(10*bulletSpeed, Helper::degToRad(shotAngle));

        x += coordX;
        y += coordY;

        //инициализация новой пули
        entiyes.emplace_back(new Bullet(x, y, shotAngle, bulletDamage, bulletSpeed, friendly));

        shotAngle += sideShift;
    }
    return true;
}


