#include "shotGun.h"
#include "weapon.h"
#include "bullet.h"

int shotGun::Shot(double X_coord, double Y_coord, int rotation)
{
    double fin_X_coord = 0, fin_Y_coord = 0;


    int d = 0 - bulletCount / 2;
    int fl = 0;
    int j = 0;
    //если оружие выстреливает больше 0 пуль и на карте ни одной пули
    if (bulletCount > 0 && countActiveBullets == 0)
    {
        for (int i = 0; i < bulletCount; i++)
        {

            //выбор типа оружия
            double x, y;
            x = X_coord;
            y = Y_coord;
            //выбор координа в зависимости от направления
            switch (rotation)
            {
            case 0:
                fin_X_coord = X_coord - 4;
                fin_Y_coord = Y_coord + d;
                y += d;
                break;
            case 1:
                fin_X_coord = X_coord + d;
                fin_Y_coord = Y_coord + 4;
                x += d;
                break;
            case 2:
                fin_X_coord = X_coord + 4;
                fin_Y_coord = Y_coord + d;
                y += d;
                break;
            case 3:
                fin_X_coord = X_coord + d;
                fin_Y_coord = Y_coord - 4;
                x += d;
                break;
            }
            d += 1;
            // инициализация пуль
            for (int fl = 1; j < 10 && fl; j++)
                if (activeBullets[j] == 0)
                {
                    bulls[j] = new bullet(x, y, fin_X_coord, fin_Y_coord, damage, speed);
                    countActiveBullets += 1;
                    activeBullets[j] = 1;
                    fl = 0;
                }
        }
    }
    else
        fl = 1;
    return fl;
}