#include "player.h"


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

int player::getPlayerRotation()
{
    return playerRotation;
}
