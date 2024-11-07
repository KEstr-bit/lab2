#include "shotGun.h"

int shotGun::shot(double coord_X, double coord_Y, double shot_corner, std::vector<bullet>& bullets)
{

    double sideShift = 30 / (this->bulletCount-1);
    shot_corner -= 30 / 2;
    

        for (int i = 0; i < bulletCount; i++)
        {
            double cosi = cos(shot_corner * 3.14 / 180);
            double sinu = sin(shot_corner * 3.14 / 180);

            double x, y;
            x = this->bulletSpeed*cosi;
            y = this->bulletSpeed * sinu;
            
            x += coord_X;
            y += coord_Y;


            bullets.emplace_back(x, y, shot_corner, bulletDamage, bulletSpeed);

            shot_corner += sideShift;
        }

    return 0;
}