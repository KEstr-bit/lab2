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
    //копирование premap в map
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
    this->monster->enemyMovment(worldMap, mapSizeX, you);     //движение врага
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
                if(isWall(worldMap, mapSizeX, bulletCoordX, bulletCoordY))
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
                if (isWall(worldMap, mapSizeX, bulletCoordX, bulletCoordY))
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

int game::vivod()
{

    int EntityCoordX, EntityCoordY;

    static char* firstBuffer = (char*)calloc(mapSizeX * mapSizeY, sizeof(char));
    static char* secondBuffer = (char*)calloc(mapSizeX * mapSizeY, sizeof(char));

    if (firstBuffer == NULL || secondBuffer == NULL)
    {
        return 1;
    }

    //копирование карты в динамический массив
    for (int i = 0; i < mapSizeX; i++)
        for (int j = 0; j < mapSizeY; j++)
        {
            firstBuffer[i * mapSizeX + j] = worldMap[i * mapSizeX + j];
        }


    //если игрок живой
    if (!you->getEntityCoord(&EntityCoordX, &EntityCoordY))
    {
        СardinalDirections rotPlayer;
        rotPlayer = you->getPlayerDirection();

        switch (rotPlayer)
        {
        case North: firstBuffer[EntityCoordX * mapSizeX + EntityCoordY] = 'N'; break;
        case East: firstBuffer[EntityCoordX * mapSizeX + EntityCoordY] = 'E'; break;
        case South: firstBuffer[EntityCoordX * mapSizeX + EntityCoordY] = 'S'; break;
        case West: firstBuffer[EntityCoordX * mapSizeX + EntityCoordY] = 'W'; break;
        }
    }

    if (!monster->getEntityCoord(&EntityCoordX, &EntityCoordY))
    {
        firstBuffer[EntityCoordX * mapSizeX + EntityCoordY] = 'M';
    }

    //отображение пуль
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
    //вывод новой карты
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
