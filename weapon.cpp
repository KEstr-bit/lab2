#include "weapon.h"

weapon::weapon(int bulletCount, double bulletSpeed, int bulle_Damage)
{
    this->bulletDamage = bulletDamage;
    this->bulletCount = bulletCount;
    this->bulletSpeed = bulletSpeed;

}

weapon::weapon()
{
    bulletCount = 3;
    bulletSpeed = 0.5;
    bulletDamage = 50;
}

weapon::~weapon()
{
}

