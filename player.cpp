#include "player.h"



player::player(double coordX, double coordY, double speed, int hitPoints, int damage)
{
    this->damage = damage;
    this->hitPoints = hitPoints;
    this->coordX = coordX;
    this->coordY = coordY;
    this->speed = speed;

    activeWeapon = ShotGun;
    firstGun = new shotGun();
    secondGun = new avtomat();

    viewAngle = 0;
}

player::player()
{
    coordX = 7;
    coordY = 2;
    hitPoints = 100;
    speed = 0.05;
    damage = 50;

    activeWeapon = ShotGun;
    firstGun = new shotGun();
    secondGun = new avtomat();

    viewAngle = 0;
}

player::~player()
{
}


int player::playerMapStep(ÑardinalDirections stepDirection, GameMap* map)
{
    if (hitPoints > 0)
    {
        double oldAngle = viewAngle;

        switch (stepDirection)
        {
        case East: viewAngle -= 90; break;
        case South: viewAngle += 180; break;
        case West: viewAngle += 90; break;
        default: break;
        }

        this->entityMapStep(map);
        viewAngle = oldAngle;

    }
    return 0;
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

int player::shot(std::map<int, entity*> &entiyes)
{
    switch (activeWeapon)
    {
    case ShotGun:   
        this->firstGun->shot(coordX, coordY, viewAngle, entiyes);
        break;
    case Automat:
        this->secondGun->shot(coordX, coordY, viewAngle, entiyes);
        break;
    }

    return activeWeapon;
};

void player::changeVision(ÑardinalDirections direct)
{
    switch (direct)
    {
    case East:
        viewAngle -= VISION_SPEED;
        break;
    case West:
        viewAngle += VISION_SPEED;
        break;
    default:
        break;
    };

    if (viewAngle > 360)
    {
        viewAngle -= 360;
    }

    if (viewAngle < 0)
    {
        viewAngle += 360;
    }


    

};

bool player::entityMovment(GameMap* map, double playerX, double playerY)
{
    return false;
}