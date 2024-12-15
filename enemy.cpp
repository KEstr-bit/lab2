#include "Enemy.h"
#include "Helper.h"

const double Enemy::VISION_STEP = 0.2;

Enemy::Enemy(const double cordX, const double cordY, const double speed, const double hitPoints, const double damage, const double size,
    const TextureType texture, Entity* target) : Entity(cordX, cordY, speed, hitPoints, damage, size, texture, false)
{
    this->target = target;
}



double Enemy::lookAtTarget(GameMap& map)
{
    double distance = 0;
    if (isTargetSeen(map))
    {
        double targetX, targetY;
        target->getCords(targetX, targetY);

        const double deltaX = targetX - cordX;
        const double deltaY = targetY - cordY;

        distance = Helper::calcDistance(targetX, targetY,
            cordX, cordY);
        const double angleCos = deltaX / distance;
        const double angleSin = deltaY / distance;
        viewAngle = Helper::radToDeg(atan2(angleSin, angleCos));
    }
    return distance;
}

bool Enemy::update(GameMap& map, std::vector<Entity*>& entities)
{
    lookAtTarget(map);

    if (isAlive())
        return false;

    return true;
}

Entity* Enemy::getTarget() const
{
    return target;
}
