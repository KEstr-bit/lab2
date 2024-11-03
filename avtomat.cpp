#include "avtomat.h"

int avtomat::shot(double coord_X, double coord_Y, ÑardinalDirections shot_Direction, std::vector<bullet>& bullets)
{
    double final_coord_X = 0, final_coord_Y = 0;

    int sideShift = 0 - bulletCount / 2;

        for (int i = 0; i < bulletCount; i++)
        {
            double x, y;
            x = coord_X;
            y = coord_Y;
            //âûáîð êîîðäèíà â çàâèñèìîñòè îò íàïðàâëåíèÿ
            switch (shot_Direction)
            {
            case North:
                final_coord_X = coord_X - 10;
                final_coord_Y = coord_Y;
                x -= sideShift;
                break;
            case East:
                final_coord_X = coord_X;
                final_coord_Y = coord_Y + 10;
                y += sideShift;
                break;
            case South:
                final_coord_X = coord_X + 10;
                final_coord_Y = coord_Y;
                x += sideShift;
                break;
            case West:
                final_coord_X = coord_X;
                final_coord_Y = coord_Y - 10;
                y -= sideShift;
                break;
            }
            sideShift += 1;

            bullets.emplace_back(x, y, final_coord_X, final_coord_Y, bulletDamage, bulletSpeed);

        }
    

    return 0;
}