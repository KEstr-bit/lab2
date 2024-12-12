#include "Rifle.h"
#include "Helper.h"
#include "Bullet.h"

Rifle::Rifle(bool friendly)
{
    this->friendly = friendly;
    texture = AVT;
    bulletDamage = 100;
    bulletSpeed = 0.3;
}

Rifle::Rifle()
{
    texture = AVT;
    bulletDamage = 100;
}

bool Rifle::shot(double coordX, double coordY, double shotAngle, std::vector<Entity*>& entiyes)
{

    if (ammunition < bulletCount)
        return false;

	if (eventFl)
		return true;

    ammunition -= bulletCount;
  
    eventFl = true;
    textureX = 0;
    textureY = 1;

    //смещение пули от точки выстрела
    double sideShift = 0.25;

    for (int i = 0; i < bulletCount; i++)
    {
        sideShift += bulletSpeed;

        double x, y;
        x = Helper::projectionToX(sideShift, Helper::degToRad(shotAngle));
        y = Helper::projectionToY(sideShift, Helper::degToRad(shotAngle));

        x += coordX;
        y += coordY;

        //инициализация новой пули
        entiyes.emplace_back(new Bullet(x, y, shotAngle, bulletDamage, bulletSpeed, friendly));

    }
    return true;
}
