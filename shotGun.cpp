#include "shotGun.h"

int shotGun::shot(double coord_X, double coord_Y, СardinalDirections shot_Direction, std::vector<bullet>& bullets)
{
    double final_coord_X = 0, final_coord_Y = 0;

    int sideShift = 0 - bulletCount / 2;


        for (int i = 0; i < bulletCount; i++)
        {

            double x, y;
            x = coord_X;
            y = coord_Y;
            //выбор координа в зависимости от направления
            switch (shot_Direction)
            {
            case North:
                final_coord_X = coord_X - 4;
                final_coord_Y = coord_Y + sideShift;
                y += sideShift;
                break;
            case East:
                final_coord_X = coord_X + sideShift;
                final_coord_Y = coord_Y + 4;
                x += sideShift;
                break;
            case South:
                final_coord_X = coord_X + 4;
                final_coord_Y = coord_Y + sideShift;
                y += sideShift;
                break;
            case West:
                final_coord_X = coord_X + sideShift;
                final_coord_Y = coord_Y - 4;
                x += sideShift;
                break;
            }
            sideShift += 1;
            // инициализация пуль

                    bullets.emplace_back(x, y, final_coord_X, final_coord_Y, bulletDamage, bulletSpeed);


        }

    return 0;
}