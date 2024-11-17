#include "shotGun.h"
#include "helper.h"
#include "bullet.h"

void shotGun::shot(double coordX, double coordY, double shotAngle, std::map<int, entity*>& entiyes)
{
    //смещение угла полета
    double sideShift = SPREAD_ANGLE / (bulletCount - 1);
    shotAngle -= SPREAD_ANGLE / 2;

    for (int i = 0; i < bulletCount; i++)
    {
        double x, y;
        x = projectionToX(bulletSpeed, degToRad(shotAngle));
        y = projectionToY(bulletSpeed, degToRad(shotAngle));

        x += coordX;
        y += coordY;

        //инициализация новой пули
        entiyes.emplace(entity::lastID, new bullet(x, y, shotAngle, bulletDamage, bulletSpeed));

        shotAngle += sideShift;
    }
}