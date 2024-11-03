#include <iostream>
#include "game.h"
#include "entity.h"
#include "player.h"
#include "enemy.h"
#include "helper.h"


game::game()
{
    you = new player();
    monster = new enemy();
}

game::~game()
{
}

int game::allBulletMovment()
{

    for (int i = 0; i < bullets.size(); i++)
    {
        bullets[i].bulletMovment();

    }
    return 0;
}

int game::interaction(char world_Map[MAP_SIZE_X][MAP_SIZE_Y])
{

    
    this->allBulletMovment();                    //движение пуль

    int monsterIsAlive = 0;
    int monsterCoordX, monsterCoordY;
    if (!monster->getEntityCoord(&monsterCoordX, &monsterCoordY))
    {
        monsterIsAlive = 1;
    }

    int playerCoordX, playerCoordY;
    if (!you->getEntityCoord(&playerCoordX, &playerCoordY) && monsterIsAlive)
    {
        this->monster->enemyMovment(world_Map[0], MAP_SIZE_X, playerCoordX, playerCoordY);     //движение врага
        //если враг достиг игрока
        if (monsterCoordX == playerCoordX && monsterCoordY == playerCoordY)
        {
            you->attackEntity(monster->getEntityDamage());
        }
    }
 

    //если на карте есть пули первого оружия
        for (int i = 0; i < bullets.size(); i++)
        {

                int bulletCoordX, bulletCoordY;
                int bulletFinalCoordX, bulletFinalCoordY;

                bullets[i].getBulletCoords(&bulletFinalCoordX, &bulletFinalCoordY);
                bullets[i].getEntityCoord(&bulletCoordX, &bulletCoordY);
                

                //если пуля столкнулась со стеной
                if(isWall(world_Map[0], MAP_SIZE_X, bulletCoordX, bulletCoordY))
                {
                    bullets.erase(bullets.begin() + i);
                }
                else
                {
                    
                    //если пуля попала во врага

                    if (bulletCoordX == monsterCoordX && bulletCoordY == monsterCoordY && monsterIsAlive)
                    {
                        monster->attackEntity(bullets[i].getEntityDamage());
                        bullets.erase(bullets.begin() + i);

                    }
                    else
                    {
                        //если пуля достигла своей конечной точки
                        if (bulletCoordX == bulletFinalCoordX && bulletCoordY == bulletFinalCoordY)
                        {
                            bullets.erase(bullets.begin() + i);
                        }
                    }
                }
            }
        

    return 0;
}
