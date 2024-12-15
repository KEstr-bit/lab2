#include "Bullet.h"

Bullet::Bullet(const double cordX, const double cordY, const double flightAngle, const double speed, const double hitPoints, const double damage,
    const TextureType texture, const bool friendly): Entity(cordX, cordY, speed, hitPoints, damage, 0.5 ,texture, friendly)
{
    viewAngle = flightAngle;
}

bool Bullet::update(GameMap& map, std::vector<Entity*>& entities)
{
    updateAnimation();

    if (eventFl)
        return false;

    if (!isAlive())
        return true;

    baseStep();
	hitPoints -= speed;

    //если пуля врезалась в стену
    if (map.isWall(cordX, cordY))
        kill();

    return false;
}


