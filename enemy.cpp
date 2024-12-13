#include "Enemy.h"
#include "Helper.h"

const double Enemy::VISION_STEP = 0.2;

Enemy::Enemy(const double cordX, const double cordY, const double speed, const double hitPoints, const double damage, const double size,
    const TextureType texture, Entity* target) : Entity(cordX, cordY, speed, hitPoints, damage, size, texture, false)
{
    this->target = target;
}

bool Enemy::isTargetSeen(GameMap& map)
{
    double targetX, targetY;
    target->getCords(targetX, targetY);

    double enemyX, enemyY;
    this->getCords(enemyX, enemyY);

    bool visionFl = true;
    double distance = Helper::calcDistance(enemyX, enemyY, targetX, targetY);

    viewAngle += std::atan2((targetX - enemyX) / distance, (targetY - enemyY) / distance);

    //движение луча взгляда к игроку
    while (distance > VISION_STEP && visionFl)
    {
        enemyX = Helper::interpolateCoords(enemyX, targetX, VISION_STEP, distance);
        enemyY = Helper::interpolateCoords(enemyY, targetY, VISION_STEP, distance);

        distance = Helper::calcDistance(enemyX, enemyY, targetX, targetY);

        //если луч столкнулся со стеной
        if (map.isWall(enemyX, enemyY))
            visionFl = false;
    }

    return visionFl;
}

double Enemy::updateAngle()
{

    double targetX, targetY;
    target->getCords(targetX, targetY);

    const double deltaX = targetX - cordX;
    const double deltaY = targetY - cordY;

    const double distance = Helper::calcDistance(targetX, targetY, cordX, cordY);
    const double angleCos = deltaX / distance;
    const double angleSin = deltaY / distance;
    viewAngle = Helper::radToDeg(atan2(angleSin, angleCos));
    return distance;
}
