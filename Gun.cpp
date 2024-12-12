#include "Gun.h"

Gun::Gun(int bulletCount, double bulletSpeed, int bulletDamage, bool friendly): magazineCapacity(10)
{
	this->bulletDamage = bulletDamage;
	this->bulletCount = bulletCount;
	this->bulletSpeed = bulletSpeed;
	this->friendly = friendly;
}

Gun::Gun(): magazineCapacity(10)
{
	bulletCount = 1;
	bulletSpeed = 0.05;
	bulletDamage = 50;
	friendly = false;
}

Gun::Gun(bool friendly): magazineCapacity(10)
{
	bulletCount = 1;
	bulletSpeed = 0.05;
	bulletDamage = 50;
	this->friendly = friendly;
}

Gun::~Gun()
{
}

void Gun::update()
{
	textureX += Entity::FRAME_SPEED;
	if (Helper::myRound(textureX) >= TexturePack::FRAMES_COUNT)
	{
		textureX = 0;
		textureY = 0;
		eventFl = false;
	}
}

