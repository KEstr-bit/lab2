#include "avtomat.h"

int avtomat::shot(double coordX, double coordY, double shotAngle, std::vector<bullet>& bullets)
{
    double sideShift = 0;

        for (int i = 0; i < bulletCount; i++)
        {
            sideShift += bulletSpeed;

            double x, y;
            x = projectionToX(sideShift, degToRad(shotAngle));
            y = projectionToY(sideShift, degToRad(shotAngle));
            
            x += coordX;
            y += coordY;

            bullets.emplace_back(x, y, shotAngle, this->bulletDamage, this->bulletSpeed);

        }
    

    return 0;
}