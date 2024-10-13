#include "enemy.h"
#include "helper.h"
#include <iostream>
#include <windows.h>

enemy::enemy(double x, double y, int hp, int dm, double sp)
{
    Damage = dm;
    Hit_Points = hp;
    X_Coord = x;
    Y_Coord = y;
    speed = sp;
}

enemy::enemy()
{
    Damage = 50;
    Hit_Points = 100;
    X_Coord = 1;
    Y_Coord = 8;
    speed = 0.2;
}

enemy::~enemy()
{
}

int enemy::enemyMovment(char* map, int Map_Size_X, player* pl)
{
    int i = 0;      //флаг живого игрока
    double player_x, player_y;
    int roundX, roundY;
    pl->getEntityCoord(&player_x, &player_y);
    roundX = roundd(X_Coord);
    roundY = roundd(Y_Coord);

    //если враг живой
    if (Hit_Points > 0)
    {
        if (playersVision(map, Map_Size_X, pl))
        {
            if (abss(X_Coord - player_x) > abss(Y_Coord - player_y))
            {
                if (*(map + (roundX + 1) * Map_Size_X + roundY) != '#' && X_Coord < player_x)
                    this->entityStep(South);
                else
                    if (*(map + (roundX - 1) * Map_Size_X + roundY) != '#' && X_Coord > player_x)
                        this->entityStep(North);

            }
            else
            {
                if (*(map + (roundX)*Map_Size_X + roundY - 1) != '#' && Y_Coord > player_y)
                    this->entityStep(West);
                else
                    if (*(map + (roundX)*Map_Size_X + roundY + 1) != '#' && Y_Coord < player_y)
                        this->entityStep(East);
            }
        }
        else
        {
            switch (rand() % 10)
            {
            case 0:
                if (*(map + (roundX + 1) * Map_Size_X + roundY) != '#')
                    this->entityStep(South); break;
            case 1:
                if (*(map + (roundX - 1) * Map_Size_X + roundY) != '#')
                    this->entityStep(North); break;
            case 2:
                if (*(map + (roundX)*Map_Size_X + roundY - 1) != '#')
                    this->entityStep(West); break;
            case 3:
                if (*(map + (roundX)*Map_Size_X + roundY + 1) != '#')
                    this->entityStep(East); break;
            default: break;
            }
        }
    }

    return 0;
}

int enemy::playersVision(char* map, int Map_Size_X, player* pl)
{
    double player_x, player_y;
    double x, y;
    int roundX, roundY;
    x = X_Coord;
    y = Y_Coord;

    pl->getEntityCoord(&player_x, &player_y);

    int fl = 1;
    double d = sqrt((x - player_x) * (x - player_x) + (y - player_y) * (y - player_y));

    //проверка: видит ли враг игрока
    while (d > speed && fl)
    {


        x = (K * player_x + (d - K) * x) / d;
        y = (K * player_y + (d - K) * y) / d;
        d = sqrt((x - player_x) * (x - player_x) + (y - player_y) * (y - player_y));

        roundX = roundd(x);
        roundY = roundd(y);

        if (*(map + roundX * Map_Size_X + roundY) == '#')
            fl = 0;

    }

    return fl;
}
