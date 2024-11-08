#include "enemy.h"
#include "helper.h"
#include <windows.h>

const double enemy::VISSION_STEP = 0.2;

enemy::enemy(double coordX, double coordY, double speed, int hitPoints, int damage)
{
    this->damage = damage;
    this->hitPoints = hitPoints;
    this->coordX = coordX;
    this->coordY = coordY;
    this->speed = speed;
}

enemy::enemy()
{
    damage = 50;
    hitPoints = 100;
    coordX = 1;
    coordY = 8;
    speed = 0.02;
}

enemy::~enemy()
{
}

int enemy::enemyMovment(GameMap* map, double playerX, double playerY)
{
    double deltaX = playerX - this->coordX;
    double deltaY = playerY - this->coordY;

    if (playersVision(map, playerX, playerY))
    {
        double distance = calcDistance(playerX, playerY, this->coordX, this->coordY);
        double angleCos = deltaX / distance;
        double angleSin = deltaY / distance;
        this->viewAngle = radToDeg(atan2(angleSin, angleCos));
        this->entityMapStep(map);
    }

    return 0;
}


bool enemy::playersVision(GameMap* map, double playerX, double playerY)
{
    if (hitPoints > 0)
    {
        double enemyX, enemyY;
        this->getEntityCoord(&enemyX, &enemyY);

        bool fl = true;
        double distance = calcDistance(enemyX, enemyY, playerX, playerY);

        //проверка: видит ли враг игрока
        while (distance > VISSION_STEP && fl)
        {
            enemyX = interpolateCoord(enemyX, playerX, VISSION_STEP, distance);
            enemyY = interpolateCoord(enemyY, playerY, VISSION_STEP, distance);

            distance = calcDistance(enemyX, enemyY, playerX, playerY);

            if (map->isWall(enemyX, enemyY))
                fl = false;
        }

        return fl;
    } 
    return false;
}
