#include "avtomat.h"

int avtomat::shot(double coord_X, double coord_Y, double shot_corner, std::vector<bullet>& bullets)
{
    double cosi = cos(shot_corner * 3.14 / 180);
    double sinu = sin(shot_corner * 3.14 / 180);
    
    int sideShift = 0;
        for (int i = 0; i < bulletCount; i++)
        {
            sideShift += this->bulletSpeed;
            double x, y;
            x = sideShift*cosi;
            y = sideShift*sinu;
            
            x += coord_X;
            y += coord_Y;

            bullets.emplace_back(x, y, shot_corner, this->bulletDamage, this->bulletSpeed);

        }
    

    return 0;
}