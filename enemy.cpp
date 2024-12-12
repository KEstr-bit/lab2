#include "enemy.h"
#include "helper.h"

const double enemy::VISION_STEP = 0.2;

enemy::enemy(double coordX, double coordY, double speed, int hitPoints, int damage, Player* player)
{
    this->damage = damage;
    this->hitPoints = hitPoints;
    this->cordX = coordX;
    this->cordY = coordY;
    this->speed = speed;
    this->player = player;
}

enemy::enemy(Player* player)
{
    damage = 50;
    hitPoints = 100;
    cordX = 1;
    cordY = 8;
    speed = 0.02;
    this->player = player;
}

enemy::enemy()
{
    damage = 50;
    hitPoints = 100;
    cordX = 1;
    cordY = 8;
    speed = 0.02;
    this->player = nullptr;
}

enemy::~enemy()
{
}


bool enemy::update(GameMap* map, std::vector<Entity*>& entities)
{
    frameShift();

    if (eventFl)
        return false;

    if (!this->isAlive())
            return true;

    double playerX, playerY;
    player->getEntityCord(&playerX, &playerY);

    double deltaX = playerX - this->cordX;
    double deltaY = playerY - this->cordY;

    //если враг видит игрока
    if (playersVision(map))
    {
        
        double distance = helper::calcDistance(playerX, playerY, this->cordX, this->cordY);
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
    player->getEntityCord(&playerX, &playerY);

    double enemyX, enemyY;
    this->getEntityCord(&enemyX, &enemyY);

    
    bool flVission = true;
    double distance = helper::calcDistance(enemyX, enemyY, playerX, playerY);

    viewAngle += std::atan2((playerX - enemyX) / distance, (playerY - enemyY) / distance);

    //движение луча взгляда к игроку
    while (distance > VISION_STEP && flVission)
    {
        enemyX = helper::interpolateCoord(enemyX, playerX, VISION_STEP, distance);
        enemyY = helper::interpolateCoord(enemyY, playerY, VISION_STEP, distance);

        distance = helper::calcDistance(enemyX, enemyY, playerX, playerY);

        //если луч столкнулся со стеной
        if (map->isWall(enemyX, enemyY))
            flVission = false;
    }

    return flVission;
}
