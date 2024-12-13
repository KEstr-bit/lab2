#include "Rifle.h"
#include "Helper.h"
#include "Bullet.h"


Rifle::Rifle(const int magazineCapacity, const int bulletCount, const double bulletSpeed, const double bulletDamage, const TextureType bulletTexture,
    const bool friendly) : Gun(magazineCapacity, bulletCount, bulletSpeed, bulletDamage, friendly, RIFLE, bulletTexture) {}

bool Rifle::shot(const double cordX, const double cordY, const double shotAngle, std::vector<Entity*>& entities)
{

    if (ammunition < bulletCount){
        return false;
    }

    if (eventFl) {
        return true;
    }

    ammunition -= bulletCount;
    startAnimation(ANIM_ATTACK1);

    //смещение пули от точки выстрела
    double sideShift = SIDE_SHIFT;

    for (int i = 0; i < bulletCount; i++)
    {
        sideShift += bulletSpeed;

        double x = Helper::projectToX(sideShift, Helper::degToRad(shotAngle));
        double y = Helper::projectToY(sideShift, Helper::degToRad(shotAngle));

        x += cordX;
        y += cordY;

        //инициализация новой пули
        entities.emplace_back(new Bullet(x, y, shotAngle, bulletSpeed, 10, bulletDamage, bulletTexture, friendly));

    }
    return true;
}
