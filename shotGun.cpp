#include "shotGun.h"
#include "helper.h"
#include "bullet.h"

void shotGun::shot(double coordX, double coordY, double shotAngle, std::map<int, Entity*>& entiyes)
{
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
        x = helper::projectionToX(bulletSpeed, helper::degToRad(shotAngle));
        y = helper::projectionToY(bulletSpeed, helper::degToRad(shotAngle));

        x += coordX;
        y += coordY;

        //инициализация новой пули
        entiyes.emplace(Entity::lastID, new bullet(x, y, shotAngle, bulletDamage, bulletSpeed));

        shotAngle += sideShift;
    }
}