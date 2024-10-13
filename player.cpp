#include "player.h"


int player::gamePlayerStep(char* map, int Map_Size_X, ÑardinalDirections rot)
{

    int fl = 0;
    if (Hit_Points > 0)
    {
        int roundX, roundY;
        this->getEntityCoord(&roundX, &roundY);


        //èçìåíåíèå êîîðäèíàò èãðîêà â çàâèñèìîñòè îò íàïðàâëåíèÿ
        switch (rot)
        {
        case North:
            if (*(map + (roundX - 1) * Map_Size_X + roundY) != '#')
                this->playerStep(North);
            else
                fl = 2;
            break;
        case East:
            if (*(map + (roundX)*Map_Size_X + roundY + 1) != '#')
                this->playerStep(East);
            else
                fl = 2;
            break;
        case South:
            if (*(map + (roundX + 1) * Map_Size_X + roundY) != '#')
                this->playerStep(South);
            else
                fl = 2;
            break;
        case West:
            if (*(map + (roundX)*Map_Size_X + roundY - 1) != '#')
                this->playerStep(West);
            else
                fl = 2;
            break;
        default:
            fl = 1;
        }
    }
    return fl;
}

player::player(double x, double y, double sp, int hp, int dm, ÑardinalDirections rotation)
{
    Damage = dm;
    Hit_Points = hp;
    X_Coord = x;
    Y_Coord = y;
    speed = sp;
    playerRotation = rotation;
    gun = new shotGun();
}

player::player()
{
    X_Coord = 8;
    Y_Coord = 1;
    Hit_Points = 100;
    speed = 1;
    Damage = 50;
    playerRotation = North;
    gun = new shotGun();

}

player::~player()
{
}


int player::playerStep(ÑardinalDirections rotation)
{
    int i = 0;
    playerRotation = rotation;
    switch (rotation)
    {
    case 0: X_Coord -= speed; break;
    case 1: Y_Coord += speed; break;
    case 2: X_Coord += speed; break;
    case 3: Y_Coord -= speed; break;
    default: i = 1;
    }

    return i;

}

ÑardinalDirections player::getPlayerRotation()
{
    return playerRotation;
}
