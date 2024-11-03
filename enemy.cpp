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

int enemy::enemyMovment(char* world_Map, int map_Size_X, double player_X, double player_Y)
{
    int enemyRoundX, enemyRoundY;

    this->getEntityCoord(&enemyRoundX, &enemyRoundY);

    double deltaX = player_X - coordX;
    double deltaY = player_Y - coordY;

    //если враг живой
    if (hitPoints > 0)
    {
        if (playersVision(world_Map, map_Size_X, player_X, player_Y))
        {
            if (abss(deltaX) > abss(deltaY))
            {
                if (!isWall(world_Map, map_Size_X, enemyRoundX + 1, enemyRoundY) && deltaX > 0)
                    this->entityStep(South);
                else
                    if (!isWall(world_Map, map_Size_X, enemyRoundX - 1, enemyRoundY) && deltaX < 0)
                        this->entityStep(North);

            }
            else
            {
                if (!isWall(world_Map, map_Size_X, enemyRoundX, enemyRoundY - 1) && deltaY < 0)
                    this->entityStep(West);
                else
                    if (!isWall(world_Map, map_Size_X, enemyRoundX, enemyRoundY + 1) && deltaY > 0)
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

int enemy::playersVision(char* world_map, int map_Size_X, double player_X, double player_Y)
{
    double enemyX, enemyY;

    this->getEntityCoord(&enemyX, &enemyY);

    int fl = 1;
    double distance = calcDistance(enemyX, enemyY, player_X, player_Y);

    //проверка: видит ли враг игрока
    while (distance > speed && fl)
    {


        enemyX = (K * player_X + (distance - K) * enemyX) / distance;
        enemyY = (K * player_Y + (distance - K) * enemyY) / distance;

        distance = calcDistance(enemyX, enemyY, player_X, player_Y);

        if ( isWall( world_map, map_Size_X, roundd(enemyX), roundd(enemyY) ) )
            fl = 0;

    }

    return fl;
}
