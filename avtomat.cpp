#include "avtomat.h"
#include "helper.h"
#include "bullet.h"

avtomat::avtomat(bool friendly)
{
    this->friendly = friendly;
    texture = AVT;
    bulletDamage = 100;
    bulletSpeed = 0.3;
}

avtomat::avtomat()
{
    texture = AVT;
    bulletDamage = 100;
}

bool avtomat::shot(double coordX, double coordY, double shotAngle, std::vector<Entity*>& entiyes)
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
        x = helper::projectionToX(sideShift, helper::degToRad(shotAngle));
        y = helper::projectionToY(sideShift, helper::degToRad(shotAngle));

        x += coordX;
        y += coordY;

        //инициализация новой пули
        entiyes.emplace_back(new bullet(x, y, shotAngle, bulletDamage, bulletSpeed, friendly));

    }
    return true;
}
