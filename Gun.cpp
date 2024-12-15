#include "Gun.h"

Gun::Gun(const int magazineCapacity, const int bulletCount, const double bulletSpeed, const double bulletDamage,
         const bool friendly, const TextureType texture, const TextureType bulletTexture):
		magazine_capacity(magazineCapacity), texture(texture),
		bulletTexture(bulletTexture)
{
	this->bulletDamage = bulletDamage;
	this->bulletCount = bulletCount;
	this->bulletSpeed = bulletSpeed;
	this->friendly = friendly;
}

void Gun::startAnimation(const Animations animation)
{
	frame = 0;
	this->animation = animation;
	eventFl = true;
}

void Gun::startAnimation(const Animations animation, int)
{
	if(!eventFl)
		this->animation = animation;
}


void Gun::getAnimationState(Animations& animation, int& frame)
{
	frame = static_cast<int>(Helper::round(this->frame));
	animation = this->animation;
}

void Gun::updateAnimation()
{
	frame += FRAME_SPEED;
	if (Helper::round(frame) >= TexturePack::FRAMES_COUNT)
	{
		frame = 0;
		animation = ANIM_BASE;
		eventFl = false;
	}
}


void Gun::reloading()
{
	startAnimation(ANIM_ATTACK2);
	ammunition = magazine_capacity;
}

double Gun::getDamage() const
{
	return bulletDamage;
}

