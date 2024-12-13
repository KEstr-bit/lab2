#include "ShotGun.h"
#include "Helper.h"
#include "Bullet.h"

ShotGun::ShotGun(const int magazineCapacity, const int bulletCount, const double bulletSpeed, const double bulletDamage, const TextureType bulletTexture,
    const bool friendly) : Gun(magazineCapacity, bulletCount, bulletSpeed, bulletDamage, friendly, SHOTGUN, bulletTexture) {}

bool ShotGun::shot(const double cordX, const double cordY, double shotAngle, std::vector<Entity*>& entities)
{
    //смещение угла полета
    if (ammunition < bulletCount) {
        return false;
    }

    if (eventFl) {
        return true;
    }

    ammunition -= bulletCount;
    startAnimation(ANIM_ATTACK1);


    //смещение угла полета
    double angleShift = 0;
    if (bulletCount > 1)
    {
        angleShift = static_cast<double>(SPREAD_ANGLE) / (bulletCount - 1);
        shotAngle -= SPREAD_ANGLE / 2.0;
    }

    for (int i = 0; i < bulletCount; i++)
    {
	    double x = Helper::projectToX(SIDE_SHIFT, Helper::degToRad(shotAngle));
        double y = Helper::projectToY(SIDE_SHIFT, Helper::degToRad(shotAngle));

        x += cordX;
        y += cordY;

        //инициализация новой пули
        entities.emplace_back(new Bullet(x, y, shotAngle, bulletSpeed, 5, bulletDamage, bulletTexture, friendly));

        shotAngle += angleShift;
    }
    return true;
}


