#include "enemy.h"
#include "helper.h"
#include <windows.h>

enemy::enemy(double coord_X, double coord_Y, double entity_Speed, int hit_Points, int entity_Damage)
{
    damage = entity_Damage;
    hitPoints = hit_Points;
    coordX = coord_X;
    coordY = coord_Y;
    speed = entity_Speed;
}

enemy::enemy()
{
    damage = 50;
    hitPoints = 100;
    coordX = 1;
    coordY = 8;
    speed = 0.2;
}

enemy::~enemy()
{
}

int enemy::enemyMovment(char* world_Map, int map_Size_X, player* pl)
{
    int i = 0;      //флаг живого игрока
    double playerX, playerY;
    int enemyRoundX, enemyRoundY;

    pl->getEntityCoord(&playerX, &playerY);
    this->getEntityCoord(&enemyRoundX, &enemyRoundY);

    //если враг живой
    if (hitPoints > 0)
    {
        if (playersVision(world_Map, map_Size_X, pl))
        {
            if (abss(coordX - playerX) > abss(coordY - playerY))
            {
                if (!isWall(world_Map, map_Size_X, enemyRoundX + 1, enemyRoundY) && coordX < playerX)
                    this->entityStep(South);
                else
                    if (!isWall(world_Map, map_Size_X, enemyRoundX - 1, enemyRoundY) && coordX > playerX)
                        this->entityStep(North);

            }
            else
            {
                if (!isWall(world_Map, map_Size_X, enemyRoundX, enemyRoundY - 1) && coordY > playerY)
                    this->entityStep(West);
                else
                    if (!isWall(world_Map, map_Size_X, enemyRoundX, enemyRoundY + 1) && coordY < playerY)
                        this->entityStep(East);
            }
        }
        else
        {
            switch (rand() % 10)
            {
            case 0:
                if (!isWall(world_Map, map_Size_X, enemyRoundX + 1, enemyRoundY))
                    this->entityStep(South); break;
            case 1:
                if (!isWall(world_Map, map_Size_X, enemyRoundX - 1, enemyRoundY))
                    this->entityStep(North); break;
            case 2:
                if (!isWall(world_Map, map_Size_X, enemyRoundX, enemyRoundY - 1))
                    this->entityStep(West); break;
            case 3:
                if (!isWall(world_Map, map_Size_X, enemyRoundX, enemyRoundY + 1))
                    this->entityStep(East); break;
            default: break;
            }
        }
    }

    return 0;
}

int enemy::playersVision(char* world_map, int map_Size_X, player* pl)
{
    double playerX, playerY;
    double enemyX, enemyY;

    this->getEntityCoord(&enemyX, &enemyY);
    pl->getEntityCoord(&playerX, &playerY);

    int fl = 1;
    double distance = calcDistance(enemyX, enemyY, playerX, playerY);

    //проверка: видит ли враг игрока
    while (distance > speed && fl)
    {


        enemyX = (K * playerX + (distance - K) * enemyX) / distance;
        enemyY = (K * playerY + (distance - K) * enemyY) / distance;

        distance = calcDistance(enemyX, enemyY, playerX, playerY);

        if ( isWall( world_map, map_Size_X, roundd(enemyX), roundd(enemyY) ) )
            fl = 0;

    }

    return fl;
}
