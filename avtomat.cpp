#include "avtomat.h"
#include "weapon.h"
#include "bullet.h"

int avtomat::Shot(double X_coord, double Y_coord, int rotation)
{
    double fin_X_coord = 0, fin_Y_coord = 0;

    int d = 0 - bulletCount / 2;
    int fl = 0;
    int j = 0;
    //���� ������ ������������ ������ 0 ���� � �� ����� �� ����� ����
    if (bulletCount > 0 && countActiveBullets == 0)
    {
        //����� ���� ������
        double x, y;
        x = X_coord;
        y = Y_coord;
        //����� �������� � ����������� �� �����������
        switch (rotation)
        {
        case 0:
            fin_X_coord = X_coord - 10;
            fin_Y_coord = Y_coord;
            X_coord -= d;
            break;
        case 1:
            fin_X_coord = X_coord;
            fin_Y_coord = Y_coord + 10;
            Y_coord += d;
            break;
        case 2:
            fin_X_coord = X_coord + 10;
            fin_Y_coord = Y_coord;
            X_coord += d;
            break;
        case 3:
            fin_X_coord = X_coord;
            fin_Y_coord = Y_coord - 10;
            Y_coord -= d;
            break;
        }
        d += 1;
        // ������������� ����
        for (int fl = 1; j < 10 && fl; j++)
            if (activeBullets[j] == 0)
            {
                bulls[j] = new bullet(x, y, fin_X_coord, fin_Y_coord, damage, speed);
                countActiveBullets += 1;
                activeBullets[j] = 1;
                fl = 0;
            }
    }
    else
        fl = 1;
    return fl;
}