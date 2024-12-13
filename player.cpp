#include "Player.h"

Player::Player(const double cordX, const double cordY) : Entity(cordX, cordY, 0.05, 100, 50, 0.5, NECROMANCER, true)
{
	activeWeapon = GUN_SHOTGUN;
	firstGun = new ShotGun(10, 10, 0.05, 50, BULLET, true);
	secondGun = new Rifle(10, 1, 0.3, 100, BULLET, true);
}


Player::~Player()
{
    delete firstGun;
    delete secondGun;
}


void Player::playerMapStep(const CardinalDirections stepDirection, GameMap& map)
{
    getActiveWeapon()->startAnimation(ANIM_MOVE, 1);
	const double oldAngle = viewAngle;

    //изменение угла в зависимости от направления движения
    switch (stepDirection)
    {
    case EAST: viewAngle -= 90; break;
    case SOUTH: viewAngle += 180; break;
    case WEST: viewAngle += 90; break;
    case NORTH:break;
    }

    this->mapStep(map);
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
    getActiveWeapon()->startAnimation(ANIM_SPAWN);
};

void Player::shot(std::vector<Entity*>& entities) const
{

    switch (activeWeapon)
    {
    case GUN_SHOTGUN:   
        firstGun->shot(cordX, cordY, viewAngle, entities);
        break;
    case GUN_RIFLE:
        secondGun->shot(cordX, cordY, viewAngle, entities);
        break;
    }
}

Gun* Player::getActiveWeapon() const
{
	switch (activeWeapon)
	{
	case 0: return firstGun;
	case 1: return secondGun;
	}
	return nullptr;
};

void Player::changeVision(const double angle)
{
    viewAngle -= angle;

    if (viewAngle > 360)
	    viewAngle -= 360;

    if (viewAngle < 0)
	    viewAngle += 360;
};

bool Player::update(GameMap& map, std::vector<Entity*>& entities)
{
    firstGun->updateAnimation();
    secondGun->updateAnimation();
    return false;
}