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



int game::interaction(char world_Map[MAP_SIZE_X][MAP_SIZE_Y])
{
    this->monster->enemyMovment(world_Map[0], MAP_SIZE_X, you);     //движение врага
    this->you->firstGun->allBulletMovment();                    //движение пули
    this->you->secondGun->allBulletMovment();                    //движение пули

    int monsterIsAlive = 0;
    int monsterCoordX, monsterCoordY;
    if (!monster->getEntityCoord(&monsterCoordX, &monsterCoordY))
    {
        monsterIsAlive = 1;
    }
 

    //если на карте есть пули первого оружия
    if (you->firstGun->getCountActiveBullets() > 0)
    {
        for (int i = 0; i < 10; i++)
        {
            //если пуля существует
            if (you->firstGun->getActiveBullet(i) == 1)
            {
                
                int bulletCoordX, bulletCoordY;
                int bulletFinalCoordX, bulletFinalCoordY;

                you->firstGun->bullets[i]->getBulletCoords(&bulletFinalCoordX, &bulletFinalCoordY);
                you->firstGun->bullets[i]->getEntityCoord(&bulletCoordX, &bulletCoordY);
                

                //если пуля столкнулась со стеной
                if(isWall(world_Map[0], MAP_SIZE_X, bulletCoordX, bulletCoordY))
                {
                    delete you->firstGun->bullets[i];
                    you->firstGun->setActiveBullet(i, 0);
                    you->firstGun->changeCountActiveBullets(-1);
                }
                else
                {
                    
                    //если пуля попала во врага

                    if (bulletCoordX == monsterCoordX && bulletCoordY == monsterCoordY && monsterIsAlive)
                    {

                        monster->attackEntity(you->firstGun->bullets[i]->getEntityDamage());
                        delete you->firstGun->bullets[i];
                        you->firstGun->setActiveBullet(i, 0);
                        you->firstGun->changeCountActiveBullets(-1);

                    }
                    else
                    {
                        //если пуля достигла своей конечной точки
                        if (bulletCoordX == bulletFinalCoordX && bulletCoordY == bulletFinalCoordY)
                        {
                            delete you->firstGun->bullets[i];
                            you->firstGun->setActiveBullet(i, 0);
                            you->firstGun->changeCountActiveBullets(-1);
                        }
                    }
                }
            }
        }
    }

    if (you->secondGun->getCountActiveBullets() > 0)
    {
        for (int i = 0; i < 10; i++)
        {
            //если пуля существует
            if (you->secondGun->getActiveBullet(i) == 1)
            {

                int bulletCoordX, bulletCoordY;
                int bulletFinalCoordX, bulletFinalCoordY;

                you->secondGun->bullets[i]->getBulletCoords(&bulletFinalCoordX, &bulletFinalCoordY);
                you->secondGun->bullets[i]->getEntityCoord(&bulletCoordX, &bulletCoordY);


                //если пуля столкнулась со стеной
                if (isWall(world_Map[0], MAP_SIZE_X, bulletCoordX, bulletCoordY))
                {
                    delete you->secondGun->bullets[i];
                    you->secondGun->setActiveBullet(i, 0);
                    you->secondGun->changeCountActiveBullets(-1);
                }
                else
                {

                    //если пуля попала во врага
                    if (bulletCoordX == monsterCoordX && bulletCoordY == monsterCoordY && monsterIsAlive)
                    {

                        monster->attackEntity(you->secondGun->bullets[i]->getEntityDamage());
                        delete you->secondGun->bullets[i];
                        you->secondGun->setActiveBullet(i, 0);
                        you->secondGun->changeCountActiveBullets(-1);

                    }
                    else
                    {
                        //если пуля достигла своей конечной точки
                        if (bulletCoordX == bulletFinalCoordX && bulletCoordY == bulletFinalCoordY)
                        {
                            delete you->secondGun->bullets[i];
                            you->secondGun->setActiveBullet(i, 0);
                            you->secondGun->changeCountActiveBullets(-1);
                        }
                    }
                }
            }
        }
    }

    int playerCoordX, playerCoordY;
    if (!you->getEntityCoord(&playerCoordX, &playerCoordY) && monsterIsAlive)
    {
        //если враг достиг игрока
        if (monsterCoordX == playerCoordX && monsterCoordY == playerCoordY)
        {
            you->attackEntity(monster->getEntityDamage());
        }
    }
    return 0;
}

int game::vivod(char world_Map[MAP_SIZE_X][MAP_SIZE_Y])
{

    int EntityCoordX, EntityCoordY;

    static char* firstBuffer = (char*)calloc(MAP_SIZE_X * MAP_SIZE_Y, sizeof(char));
    static char* secondBuffer = (char*)calloc(MAP_SIZE_X * MAP_SIZE_Y, sizeof(char));

    if (firstBuffer == NULL || secondBuffer == NULL)
    {
        return 1;
    }

    //копирование карты в динамический массив
    for (int i = 0; i < MAP_SIZE_X; i++)
        for (int j = 0; j < MAP_SIZE_Y; j++)
        {
            firstBuffer[i * MAP_SIZE_X + j] = world_Map[i][j];
        }


    //если игрок живой
    if (!you->getEntityCoord(&EntityCoordX, &EntityCoordY))
    {
        СardinalDirections rotPlayer;
        rotPlayer = you->getPlayerDirection();

        switch (rotPlayer)
        {
        case North: firstBuffer[EntityCoordX * MAP_SIZE_X + EntityCoordY] = 'N'; break;
        case East: firstBuffer[EntityCoordX * MAP_SIZE_X + EntityCoordY] = 'E'; break;
        case South: firstBuffer[EntityCoordX * MAP_SIZE_X + EntityCoordY] = 'S'; break;
        case West: firstBuffer[EntityCoordX * MAP_SIZE_X + EntityCoordY] = 'W'; break;
        }
    }

    if (!monster->getEntityCoord(&EntityCoordX, &EntityCoordY))
    {
        firstBuffer[EntityCoordX * MAP_SIZE_X + EntityCoordY] = 'M';
    }

    //отображение пуль
    for (int i = 0; i < MAX_BULLETS; i++)
    {
        if (you->firstGun->getActiveBullet(i) == 1)
        {
            you->firstGun->bullets[i]->getEntityCoord(&EntityCoordX, &EntityCoordY);
            firstBuffer[EntityCoordX * MAP_SIZE_X + EntityCoordY] = '0';
        }
    }

    for (int i = 0; i < MAX_BULLETS; i++)
    {
        if (you->secondGun->getActiveBullet(i) == 1)
        {
            you->secondGun->bullets[i]->getEntityCoord(&EntityCoordX, &EntityCoordY);
            firstBuffer[EntityCoordX * MAP_SIZE_X + EntityCoordY] = '0';
        }
    }

    setcur(0, 0);
    //вывод новой карты
    for (int i = 0; i < MAP_SIZE_X; i++)
    {
        for (int j = 0; j < MAP_SIZE_Y; j++)
        {
            if (firstBuffer[i * MAP_SIZE_X + j] != secondBuffer[i * MAP_SIZE_X + j])
            {
                setcur(2*j, i);
                std::cout << firstBuffer[i * MAP_SIZE_X + j] << " ";
            }
        }
        std::cout << std::endl;
    }

    for (int i = 0; i < MAP_SIZE_X; i++)
        for (int j = 0; j < MAP_SIZE_Y; j++)
        {
            secondBuffer[i * MAP_SIZE_X + j] = firstBuffer[i * MAP_SIZE_X + j];
        }
    return 0;
}

