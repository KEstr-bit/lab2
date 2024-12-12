#include "Player.h"

Player::Player(double coordX, double coordY, double speed, int hitPoints, int damage)
{
    this->damage = damage;
    this->hitPoints = hitPoints;
    this->cordX = coordX;
    this->cordY = coordY;
    this->speed = speed;
    size = 0.5;
    activeWeapon = GUN_SHOTGUN;
    firstGun = new ShotGun(true);
    secondGun = new Rifle(true);
    friendly = true;
    viewAngle = 0;
}

Player::Player()
{
    cordX = 7;
    cordY = 2;
    hitPoints = 100;
    speed = 0.05;
    damage = 50;
    size = 0.5;
    activeWeapon = GUN_SHOTGUN;
    firstGun = new ShotGun(true);
    secondGun = new Rifle(true);
    friendly = true;
    viewAngle = 180;
}

Player::~Player()
{
}


void Player::playerMapStep(СardinalDirections stepDirection, GameMap* map)
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


void Player::changeActiveWeapon() 
{
    switch (activeWeapon)
    {
    case GUN_SHOTGUN:
        activeWeapon = GUN_RIFLE;
        break;
    case GUN_RIFLE:
        activeWeapon = GUN_SHOTGUN;
        break;
    }
    this->getActiveWeapon()->setAnimation(3);
};

void Player::shot(std::vector<Entity*>& entiyes)
{

    switch (activeWeapon)
    {
    case GUN_SHOTGUN:   
        this->firstGun->shot(cordX, cordY, viewAngle, entiyes);
        break;
    case GUN_RIFLE:
        this->secondGun->shot(cordX, cordY, viewAngle, entiyes);
        break;
    }
}

Gun* Player::getActiveWeapon()
{
	switch (activeWeapon)
	{
	case 0: return firstGun;
	case 1: return secondGun;
	}
	return nullptr;
};

void Player::changeVision(double angle)
{

    viewAngle -= angle;


    if (viewAngle > 360)
    {
        viewAngle -= 360;
    }

    if (viewAngle < 0)
    {
        viewAngle += 360;
    }

};

bool Player::update(GameMap* map, std::vector<Entity*>& entities)
{
    firstGun->update();
    secondGun->update();
    return false;
}