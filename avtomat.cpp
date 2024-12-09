#include "avtomat.h"
#include "helper.h"
#include "bullet.h"

void avtomat::shot(double coordX, double coordY, double shotAngle, std::map<int, entity*>& entiyes)
{
    //смещение пули от точки выстрела
    double sideShift = 0;

    for (int i = 0; i < bulletCount; i++)
    {
        sideShift += 10 * bulletSpeed;

        double x, y;
        x = helper::projectionToX(sideShift, helper::degToRad(shotAngle));
        y = helper::projectionToY(sideShift, helper::degToRad(shotAngle));

        x += coordX;
        y += coordY;

        //инициализация новой пули
        entiyes.emplace(entity::lastID, new bullet(x, y, shotAngle, this->bulletDamage, this->bulletSpeed));

    }
}