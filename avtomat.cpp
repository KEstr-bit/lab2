#include "avtomat.h"

int avtomat::shot(double coord_X, double coord_Y, �ardinalDirections shot_Direction)
{
    double final_coord_X = 0, final_coord_Y = 0;

    int sideShift = 0 - bulletCount / 2;
    int fl = 0;
    int bulletIndex = 0;
    //���� ������ ������������ ������ 0 ���� � �� ����� �� ����� ����
    if (bulletCount > 0 && countActiveBullets == 0)
    {
        for (int i = 0; i < bulletCount; i++)
        {
            double x, y;
            x = coord_X;
            y = coord_Y;
            //����� �������� � ����������� �� �����������
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
            // ������������� ����
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