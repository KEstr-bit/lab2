#include "Bomber.h"

Bomber::Bomber(double coordX, double coordY, double speed, int hitPoints, int damage, Player* player)
{
    this->damage = damage;
    this->hitPoints = hitPoints;
    this->cordX = coordX;
    this->cordY = coordY;
    this->speed = speed;
    this->player = player;
}

Bomber::Bomber(Player* player)
{
    damage = 50;
    hitPoints = 100;
    cordX = 1;
    cordY = 8;
    speed = 0.02;
    this->player = player;
}

bool Bomber::update(GameMap* map, std::vector<Entity*>& entities)
{
    static int shift = 0;
    frameShift();

    if(textureX >= 7 && textureY == 2.0 && intersects(player, 1))
    {
        player->attackEntity(damage);
        this->attackEntity(100);
    }

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
        double distance = Helper::calcDistance(playerX, playerY, this->cordX, this->cordY);
        double angleCos = deltaX / distance;
        double angleSin = deltaY / distance;
        this->viewAngle = Helper::radToDeg(atan2(angleSin, angleCos));

        this->entityMapStep(map);

        if(intersects(player, 0.7))
        {
            textureX = 0;
            textureY = 2;
            eventFl = true;
        }

    }

    return false;
}

Bomber::~Bomber()
{

}
