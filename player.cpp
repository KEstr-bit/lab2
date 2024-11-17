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

    viewAngle = 180;
}

player::~player()
{
}


void player::playerMapStep(СardinalDirections stepDirection, GameMap* map)
{
    double oldAngle = viewAngle;

    //изменение угла в зависимости от направления движения
    switch (stepDirection)
    {
    case East: viewAngle -= 90; break;
    case South: viewAngle += 180; break;
    case West: viewAngle += 90; break;
    default: break;
    }

    this->entityMapStep(map);
    //возвращение исходного угла
    viewAngle = oldAngle;
}


void player::changeActiveWeapon() 
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
};

void player::shot(std::map<int, entity*> &entiyes)
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
};

void player::changeVision(СardinalDirections direct)
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