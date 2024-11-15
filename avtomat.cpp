#include "avtomat.h"

int avtomat::shot(double coordX, double coordY, double shotAngle, std::map<int, entity*> &entiyes)
{
    double sideShift = 0;

        for (int i = 0; i < bulletCount; i++)
        {
            sideShift += 10*bulletSpeed;

            double x, y;
            x = projectionToX(sideShift, degToRad(shotAngle));
            y = projectionToY(sideShift, degToRad(shotAngle));
            
            x += coordX;
            y += coordY;

            entiyes.emplace(entity::lastID, new bullet(x, y, shotAngle, this->bulletDamage, this->bulletSpeed));

        }
    

    return 0;
}