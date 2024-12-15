#pragma once
#include "Entity.h"

class Enemy : public Entity
{
protected:
    Entity* target;

    virtual bool isTargetSeen(GameMap& map)
    {
        double targetX, targetY;
        target->getCords(targetX, targetY);

        double enemyX, enemyY;
        this->getCords(enemyX, enemyY);

        bool visionFl = true;
        double distance = Helper::calcDistance(enemyX, enemyY,
            targetX, targetY);

        viewAngle += std::atan2((targetX - enemyX) / distance, 
            (targetY - enemyY) / distance);

        //движение луча взгляда к игроку
        while (distance > VISION_STEP && visionFl)
        {
            enemyX = Helper::interpolateCords(enemyX, 
                targetX, VISION_STEP, distance);
            enemyY = Helper::interpolateCords(enemyY, 
                targetY, VISION_STEP, distance);

            distance = Helper::calcDistance(enemyX, enemyY,
                targetX, targetY);

            //если луч столкнулся со стеной
            if (map.isWall(enemyX, enemyY))
                visionFl = false;
        }

        return visionFl;
    }

public:
    static const double VISION_STEP; //шаг луча взгляда
    Enemy(double cordX, double cordY, double speed, double hitPoints, double damage, double size, TextureType texture, Entity* target);

    double lookAtTarget(GameMap& map);
    bool update(GameMap& map, std::vector<Entity*>& entities) override;
    Entity* getTarget() const;
};


