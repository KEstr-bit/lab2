#include "Bullet.h"

Bullet::Bullet(const double cordX, const double cordY, const double flightAngle, const double speed, const double hitPoints, const double damage,
    const TextureType texture, const bool friendly): Entity(cordX, cordY, speed, hitPoints, damage, 0.5 ,texture, friendly)
{
    viewAngle = flightAngle;
}

bool Bullet::update(GameMap& map, std::vector<Entity*>& entities)
{
    if (Entity::update(map, entities))
        return true;

    if (eventFl)
        return false;

    baseStep();
	hitPoints -= speed;

    //если пуля врезалась в стену
    if (map.isWall(cordX, cordY))
        kill();

    return false;
}


