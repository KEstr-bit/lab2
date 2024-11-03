#include "weapon.h"

weapon::weapon(int bullet_Count, double bullet_Speed, int bullet_Damage)
{
    bulletDamage = bullet_Damage;
    bulletCount = bullet_Count;
    bulletSpeed = bullet_Speed;

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

