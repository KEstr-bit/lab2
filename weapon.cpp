#include "weapon.h"

weapon::weapon(int bullet_Count, double bullet_Speed, int bullet_Damage)
{
    bulletDamage = bullet_Damage;
    bulletCount = bullet_Count;
    bulletSpeed = bullet_Speed;

    for (int i = 0; i < 10; i++)
        activeBullets[i] = 0;

    countActiveBullets = 0;
}

weapon::weapon()
{
    bulletCount = 3;
    bulletSpeed = 0.5;
    bulletDamage = 50;

    for (int i = 0; i < 10; i++)
        activeBullets[i] = 0;

    countActiveBullets = 0;

}

weapon::~weapon()
{
}


int weapon::getCountActiveBullets()
{
    return countActiveBullets;
}
int weapon::setActiveBullet(int index, int active)
{
    activeBullets[index] = active;
    return 0;
}
int weapon::getActiveBullet(int index)
{
    return activeBullets[index];
}
int weapon::changeCountActiveBullets(int change)
{
    countActiveBullets += change;
    return 0;
}

int weapon::allBulletMovment()
{

    for (int i = 0; i < 10; i++)
    {
        //если пуля существует
        if (activeBullets[i] == 1)
        {
            bullets[i]->bulletMovment();
        }

    }
    return 0;
}
