#include "enemy.h"
#include "helper.h"

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

bool enemy::entityMovment(GameMap* map, double playerX, double playerY)
{
    if (hitPoints <= 0)
        return true;

    double deltaX = playerX - this->coordX;
    double deltaY = playerY - this->coordY;

    //���� ���� ����� ������
    if (playersVision(map, playerX, playerY))
    {
        double distance = calcDistance(playerX, playerY, this->coordX, this->coordY);
        double angleCos = deltaX / distance;
        double angleSin = deltaY / distance;
        this->viewAngle = radToDeg(atan2(angleSin, angleCos));
        this->entityMapStep(map);
    }

    return false;
}


bool enemy::playersVision(GameMap* map, double playerX, double playerY)
{
    double enemyX, enemyY;
    this->getEntityCoord(&enemyX, &enemyY);

    bool flVission = true;
    double distance = calcDistance(enemyX, enemyY, playerX, playerY);

    //�������� ���� ������� � ������
    while (distance > VISSION_STEP && flVission)
    {
        enemyX = interpolateCoord(enemyX, playerX, VISSION_STEP, distance);
        enemyY = interpolateCoord(enemyY, playerY, VISSION_STEP, distance);

        distance = calcDistance(enemyX, enemyY, playerX, playerY);

        //���� ��� ���������� �� ������
        if (map->isWall(enemyX, enemyY))
            flVission = false;
    }

    return flVission;
}

