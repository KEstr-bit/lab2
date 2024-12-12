#include "weapon.h"

weapon::weapon(int bulletCount, double bulletSpeed, int bulletDamage, bool friendly): magazineCapacity(10)
{
	this->bulletDamage = bulletDamage;
	this->bulletCount = bulletCount;
	this->bulletSpeed = bulletSpeed;
	this->friendly = friendly;
}

weapon::weapon(): magazineCapacity(10)
{
	bulletCount = 1;
	bulletSpeed = 0.05;
	bulletDamage = 50;
	friendly = false;
}

weapon::weapon(bool friendly): magazineCapacity(10)
{
	bulletCount = 1;
	bulletSpeed = 0.05;
	bulletDamage = 50;
	this->friendly = friendly;
}

weapon::~weapon()
{
}

void weapon::update()
{
	textureX += Entity::FRAME_SPEED;
	if (helper::myRound(textureX) >= TexturePack::FRAMES_COUNT)
	{
		textureX = 0;
		textureY = 0;
		eventFl = false;
	}
}

