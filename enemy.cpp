#include "enemy.h"
#include "helper.h"

const double enemy::VISSION_STEP = 0.2;

enemy::enemy(double coordX, double coordY, double speed, int hitPoints, int damage, Player* player)
{
    this->damage = damage;
    this->hitPoints = hitPoints;
    this->coordX = coordX;
    this->coordY = coordY;
    this->speed = speed;
    this->player = player;
    avt = new avtomat();
}

enemy::enemy(Player* player)
{
    damage = 50;
    hitPoints = 100;
    coordX = 1;
    coordY = 8;
    speed = 0.02;
    this->player = player;
    avt = new avtomat();
}

enemy::~enemy()
{
}

bool enemy::entityMovment(GameMap* map, std::map<int, Entity*>& entities)
{
    textureX++;
    if (textureX > 28)
    {
        textureX = 0;
        textureY = 0;
        eventFl = false;
    }

    if(textureY == 2 && textureX == 14)
        avt->shot(coordX, coordY, viewAngle, entities);

    if (eventFl)
        return false;

    if (!this->isAlive())
            return true;

    double playerX, playerY;
    player->getEntityCoord(&playerX, &playerY);

    double deltaX = playerX - this->coordX;
    double deltaY = playerY - this->coordY;

    //если враг видит игрока
    if (playersVision(map))
    {
        if (!(rand() % 100))
        {
            textureX = 0;
            textureY = 2;
            eventFl = true;
        }
        double distance = helper::calcDistance(playerX, playerY, this->coordX, this->coordY);
        double angleCos = deltaX / distance;
        double angleSin = deltaY / distance;
        this->viewAngle = helper::radToDeg(atan2(angleSin, angleCos));
        this->entityMapStep(map);
    }

    return false;
}


bool enemy::playersVision(GameMap* map)
{
    double playerX, playerY;
    player->getEntityCoord(&playerX, &playerY);

    double enemyX, enemyY;
    this->getEntityCoord(&enemyX, &enemyY);

    
    bool flVission = true;
    double distance = helper::calcDistance(enemyX, enemyY, playerX, playerY);

    viewAngle += std::atan2((playerX - enemyX) / distance, (playerY - enemyY) / distance);

    //движение луча взгляда к игроку
    while (distance > VISSION_STEP && flVission)
    {
        enemyX = helper::interpolateCoord(enemyX, playerX, VISSION_STEP, distance);
        enemyY = helper::interpolateCoord(enemyY, playerY, VISSION_STEP, distance);

        distance = helper::calcDistance(enemyX, enemyY, playerX, playerY);

        //если луч столкнулся со стеной
        if (map->isWall(enemyX, enemyY))
            flVission = false;
    }

    return flVission;
}

