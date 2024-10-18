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
    this->monster->enemyMovment(world_Map[0], MAP_SIZE_X, you);     //�������� �����
    this->you->firstGun->allBulletMovment();                    //�������� ����
    this->you->secondGun->allBulletMovment();                    //�������� ����

    int monsterIsAlive = 0;
    int monsterCoordX, monsterCoordY;
    if (!monster->getEntityCoord(&monsterCoordX, &monsterCoordY))
    {
        monsterIsAlive = 1;
    }
 

    //���� �� ����� ���� ���� ������� ������
    if (you->firstGun->getCountActiveBullets() > 0)
    {
        for (int i = 0; i < 10; i++)
        {
            //���� ���� ����������
            if (you->firstGun->getActiveBullet(i) == 1)
            {
                
                int bulletCoordX, bulletCoordY;
                int bulletFinalCoordX, bulletFinalCoordY;

                you->firstGun->bullets[i]->getBulletCoords(&bulletFinalCoordX, &bulletFinalCoordY);
                you->firstGun->bullets[i]->getEntityCoord(&bulletCoordX, &bulletCoordY);
                

                //���� ���� ����������� �� ������
                if(isWall(world_Map[0], MAP_SIZE_X, bulletCoordX, bulletCoordY))
                {
                    delete you->firstGun->bullets[i];
                    you->firstGun->setActiveBullet(i, 0);
                    you->firstGun->changeCountActiveBullets(-1);
                }
                else
                {
                    
                    //���� ���� ������ �� �����

                    if (bulletCoordX == monsterCoordX && bulletCoordY == monsterCoordY && monsterIsAlive)
                    {

                        monster->attackEntity(you->firstGun->bullets[i]->getEntityDamage());
                        delete you->firstGun->bullets[i];
                        you->firstGun->setActiveBullet(i, 0);
                        you->firstGun->changeCountActiveBullets(-1);

                    }
                    else
                    {
                        //���� ���� �������� ����� �������� �����
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
            //���� ���� ����������
            if (you->secondGun->getActiveBullet(i) == 1)
            {

                int bulletCoordX, bulletCoordY;
                int bulletFinalCoordX, bulletFinalCoordY;

                you->secondGun->bullets[i]->getBulletCoords(&bulletFinalCoordX, &bulletFinalCoordY);
                you->secondGun->bullets[i]->getEntityCoord(&bulletCoordX, &bulletCoordY);


                //���� ���� ����������� �� ������
                if (isWall(world_Map[0], MAP_SIZE_X, bulletCoordX, bulletCoordY))
                {
                    delete you->secondGun->bullets[i];
                    you->secondGun->setActiveBullet(i, 0);
                    you->secondGun->changeCountActiveBullets(-1);
                }
                else
                {

                    //���� ���� ������ �� �����
                    if (bulletCoordX == monsterCoordX && bulletCoordY == monsterCoordY && monsterIsAlive)
                    {

                        monster->attackEntity(you->secondGun->bullets[i]->getEntityDamage());
                        delete you->secondGun->bullets[i];
                        you->secondGun->setActiveBullet(i, 0);
                        you->secondGun->changeCountActiveBullets(-1);

                    }
                    else
                    {
                        //���� ���� �������� ����� �������� �����
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
        //���� ���� ������ ������
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

    //����������� ����� � ������������ ������
    for (int i = 0; i < MAP_SIZE_X; i++)
        for (int j = 0; j < MAP_SIZE_Y; j++)
        {
            firstBuffer[i * MAP_SIZE_X + j] = world_Map[i][j];
        }


    //���� ����� �����
    if (!you->getEntityCoord(&EntityCoordX, &EntityCoordY))
    {
        �ardinalDirections rotPlayer;
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

    //����������� ����
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
    //����� ����� �����
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

