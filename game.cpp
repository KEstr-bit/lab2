#include <iostream>
#include "game.h"
#include "entity.h"
#include "player.h"
#include "enemy.h"
#include "helper.h"

game::game()
{
    mapSizeX = MAX_X;
    mapSizeY = MAX_Y;
    worldMap = (char*)calloc(mapSizeX * mapSizeY, sizeof(char));
    char preMap[MAX_X][MAX_Y] =
    {
        {'#','#','#','#','#','#','#','#','#','#'},
        {'#','.','.','.','.','.','.','.','.','#'},
        {'#','.','.','.','.','.','.','.','.','#'},
        {'#','.','.','.','.','.','.','.','.','#'},
        {'#','#','#','#','#','#','#','.','.','#'},
        {'#','.','.','.','.','.','#','.','.','#'},
        {'#','.','.','.','.','.','.','.','.','#'},
        {'#','.','.','.','#','.','.','.','.','#'},
        {'#','.','.','.','#','.','.','.','.','#'},
        {'#','#','#','#','#','#','#','#','#','#'}
    };
    //����������� premap � map
    for (int x = 0; x < mapSizeX; x++)
    {
        for (int y = 0; y < mapSizeY; y++)
        {
            *(worldMap + x * mapSizeX + y) = preMap[x][y];
        }
    }

    you = new player();
    monster = new enemy();

}

game::~game()
{
}



int game::interaction()
{
    this->monster->enemyMovment(worldMap, mapSizeX, you);     //�������� �����
    this->you->firstGun->allBulletMovment();                    //�������� ����
    this->you->secondGun->allBulletMovment();                    //�������� ����

    int monsterCoordX, monsterCoordY;
    int playerCoordX, playerCoordY;
    monster->getEntityCoord(&monsterCoordX, &monsterCoordY);
    you->getEntityCoord(&playerCoordX, &playerCoordY);

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
                if(isWall(worldMap, mapSizeX, bulletCoordX, bulletCoordY))
                {
                    delete you->firstGun->bullets[i];
                    you->firstGun->setActiveBullet(i, 0);
                    you->firstGun->changeCountActiveBullets(-1);
                }
                else
                {
                    
                    //���� ���� ������ �� �����

                    if (bulletCoordX == monsterCoordX && bulletCoordY == monsterCoordY)
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
                if (isWall(worldMap, mapSizeX, bulletCoordX, bulletCoordY))
                {
                    delete you->secondGun->bullets[i];
                    you->secondGun->setActiveBullet(i, 0);
                    you->secondGun->changeCountActiveBullets(-1);
                }
                else
                {

                    //���� ���� ������ �� �����

                    if (bulletCoordX == monsterCoordX && bulletCoordY == monsterCoordY)
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

    //���� ���� ������ ������
    if (monsterCoordX == playerCoordX && monsterCoordY == playerCoordY)
    {
        you->attackEntity(monster->getEntityDamage());
    }
    return 0;
}

int game::vivod()
{

    int EntityCoordX, EntityCoordY;

    static char* firstBuffer = (char*)calloc(mapSizeX * mapSizeY, sizeof(char));
    static char* secondBuffer = (char*)calloc(mapSizeX * mapSizeY, sizeof(char));

    if (firstBuffer == NULL || secondBuffer == NULL)
    {
        return 1;
    }

    //����������� ����� � ������������ ������
    for (int i = 0; i < mapSizeX; i++)
        for (int j = 0; j < mapSizeY; j++)
        {
            firstBuffer[i * mapSizeX + j] = worldMap[i * mapSizeX + j];
        }


    //���� ����� �����
    if (you->getEntityHitPoints() > 0)
    {
        �ardinalDirections rotPlayer;
        you->getEntityCoord(&EntityCoordX, &EntityCoordY);
        rotPlayer = you->getPlayerDirection();


        switch (rotPlayer)
        {
            case North: firstBuffer[EntityCoordX * mapSizeX + EntityCoordY] = 'N'; break;
            case East: firstBuffer[EntityCoordX * mapSizeX + EntityCoordY] = 'E'; break;
            case South: firstBuffer[EntityCoordX * mapSizeX + EntityCoordY] = 'S'; break;
            case West: firstBuffer[EntityCoordX * mapSizeX + EntityCoordY] = 'W'; break;
        }
    }

    //���� ���� �����
    if (monster->getEntityHitPoints() > 0)
    {
        monster->getEntityCoord(&EntityCoordX, &EntityCoordY);

        firstBuffer[EntityCoordX * mapSizeX + EntityCoordY] = 'M';
    }

    //����������� ����
    for (int i = 0; i < MAX_BULLETS; i++)
    {
        if (you->firstGun->getActiveBullet(i) == 1)
        {
            you->firstGun->bullets[i]->getEntityCoord(&EntityCoordX, &EntityCoordY);
            firstBuffer[EntityCoordX * mapSizeX + EntityCoordY] = '0';
        }
    }

    for (int i = 0; i < MAX_BULLETS; i++)
    {
        if (you->secondGun->getActiveBullet(i) == 1)
        {
            you->secondGun->bullets[i]->getEntityCoord(&EntityCoordX, &EntityCoordY);
            firstBuffer[EntityCoordX * mapSizeX + EntityCoordY] = '0';
        }
    }

    setcur(0, 0);
    //����� ����� �����
    for (int i = 0; i < mapSizeX; i++)
    {
        for (int j = 0; j < mapSizeY; j++)
        {
            if (firstBuffer[i * mapSizeX + j] != secondBuffer[i * mapSizeX + j])
            {
                setcur(2*j, i);
                std::cout << firstBuffer[i * mapSizeX + j] << " ";
            }
        }
        std::cout << std::endl;
    }

    for (int i = 0; i < mapSizeX; i++)
        for (int j = 0; j < mapSizeY; j++)
        {
            secondBuffer[i * mapSizeX + j] = firstBuffer[i * mapSizeX + j];
        }
    return 0;
}

int game::getWorldMap(char get_Map[MAX_X][MAX_Y])
{
    for (int i = 0; i < mapSizeX; i++)
    {
        for (int j = 0; j < mapSizeY; j++)
        {
            get_Map[i][j] = *(worldMap + i* mapSizeX + j);
        }
    }
    return 0;
}

int  game::getMapSizeX()
{
    return mapSizeX;
}
