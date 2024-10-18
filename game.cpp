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
