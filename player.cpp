#include "player.h"


int player::gamePlayerStep(char* world_Map, �ardinalDirections step_Direction)
{

    int fl = 0;
    if (hitPoints > 0)
    {
        int roundX, roundY;
        this->getEntityCoord(&roundX, &roundY);


        //��������� ��������� ������ � ����������� �� �����������
        switch (step_Direction)
        {
        case North:
            if (!isWall(world_Map, MAP_SIZE_X, roundX - 1, roundY))
                this->playerStep(North);
            else
                fl = 2;
            break;
        case East:
            if (!isWall(world_Map, MAP_SIZE_X, roundX, roundY + 1))
                this->playerStep(East);
            else
                fl = 2;
            break;
        case South:
            if (!isWall(world_Map, MAP_SIZE_X, roundX + 1, roundY))
                this->playerStep(South);
            else
                fl = 2;
            break;
        case West:
            if (!isWall(world_Map, MAP_SIZE_X, roundX, roundY - 1))
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

player::player(double coord_X, double coord_Y, double entity_Speed, int hit_Points, int entity_Damage, �ardinalDirections direction)
{
    damage = entity_Damage;
    hitPoints = hit_Points;
    coordX = coord_X;
    coordY = coord_Y;
    speed = entity_Speed;

    playerDirection = direction;
    activeWeapon = ShotGun;
    firstGun = new shotGun();
    secondGun = new avtomat();
}

player::player()
{
    coordX = 8;
    coordY = 1;
    hitPoints = 100;
    speed = 1;
    damage = 50;

    playerDirection = North;
    activeWeapon = ShotGun;
    firstGun = new shotGun();
    secondGun = new avtomat();

}

player::~player()
{
}


int player::playerStep(�ardinalDirections step_Direction)
{
    int i = 0;

    playerDirection = step_Direction;

    i = this->entityStep(step_Direction);

    return i;

}

�ardinalDirections player::getPlayerDirection()
{
    return playerDirection;
}

int player::changeActiveWeapon() 
{
    switch (activeWeapon)
    {
    case ShotGun:
        activeWeapon = Automat;
        break;
    case Automat:
        activeWeapon = ShotGun;
        break;
    }
    return activeWeapon;
};

int player::shot()
{
    switch (activeWeapon)
    {
    case ShotGun:   
        this->firstGun->shot(coordX, coordY, playerDirection);
        break;
    case Automat:
        this->secondGun->shot(coordX, coordY, playerDirection);
        break;
    }

    return activeWeapon;
};