#include "weapon.h"

weapon::weapon(int bulletCount, double bulletSpeed, int bulletDamage)
{
    this->bulletDamage = bulletDamage;
    this->bulletCount = bulletCount;
    this->bulletSpeed = bulletSpeed;

}

weapon::weapon()
{
    bulletCount = 1;
    bulletSpeed = 0.05;
    bulletDamage = 100;
}

weapon::~weapon()
{
}

