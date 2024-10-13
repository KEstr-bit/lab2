#include "shotGun.h"

int shotGun::shot(double coord_X, double coord_Y, СardinalDirections shot_Direction)
{
    double final_coord_X = 0, final_coord_Y = 0;


    int sideShift = 0 - bulletCount / 2;
    int fl = 0;
    int bulletIndex = 0;
    //если оружие выстреливает больше 0 пуль и на карте ни одной пули
    if (bulletCount > 0 && countActiveBullets == 0)
    {
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
            for (int fl = 1; bulletIndex < 10 && fl; bulletIndex++)
                if (this->getActiveBullet(bulletIndex) == 0)
                {
                    bullets[bulletIndex] = new bullet(x, y, final_coord_X, final_coord_Y, bulletDamage, bulletSpeed);
                    this->changeCountActiveBullets(1);
                    this->setActiveBullet(bulletIndex, 1);
                    fl = 0;
                }
        }
    }
    else
        fl = 1;
    return fl;
}