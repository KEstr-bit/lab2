#include "weapon.h"

weapon::weapon(int bc, double sp, int dm)
{
    damage = dm;
    bulletCount = bc;
    speed = sp;
}

weapon::weapon()
{
    bulletCount = 3;
    speed = 0.5;
    damage = 50;

}

weapon::~weapon()
{
}


int weapon::getWeaponCountBullets()
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
            bulls[i]->bulletMovment();
        }

    }
    return 0;
}
