#include "drawer.h"
#include <iostream>
#include "helper.h"

drawer::drawer()
{
	firstBuffer = (char*)calloc(MAP_SIZE_X * MAP_SIZE_Y, sizeof(char));
	secondBuffer = (char*)calloc(MAP_SIZE_X * MAP_SIZE_Y, sizeof(char));
}

drawer::~drawer()
{
}

int drawer::draw(char world_Map[MAP_SIZE_X][MAP_SIZE_Y], game* gm)
{
    int EntityCoordX, EntityCoordY;

    //копирование карты в динамический массив
    for (int i = 0; i < MAP_SIZE_X; i++)
        for (int j = 0; j < MAP_SIZE_Y; j++)
        {
            firstBuffer[i * MAP_SIZE_X + j] = world_Map[i][j];
        }


    //если игрок живой
    if (!gm->you->getEntityCoord(&EntityCoordX, &EntityCoordY))
    {
        СardinalDirections rotPlayer;
        rotPlayer = gm->you->getPlayerDirection();

        switch (rotPlayer)
        {
        case North: firstBuffer[EntityCoordX * MAP_SIZE_X + EntityCoordY] = 'N'; break;
        case East: firstBuffer[EntityCoordX * MAP_SIZE_X + EntityCoordY] = 'E'; break;
        case South: firstBuffer[EntityCoordX * MAP_SIZE_X + EntityCoordY] = 'S'; break;
        case West: firstBuffer[EntityCoordX * MAP_SIZE_X + EntityCoordY] = 'W'; break;
        }
    }

    if (!gm->monster->getEntityCoord(&EntityCoordX, &EntityCoordY))
    {
        firstBuffer[EntityCoordX * MAP_SIZE_X + EntityCoordY] = 'M';
    }

    //отображение пуль
    for (int i = 0; i < MAX_BULLETS; i++)
    {
        if (gm->you->firstGun->getActiveBullet(i) == 1)
        {
            gm->you->firstGun->bullets[i]->getEntityCoord(&EntityCoordX, &EntityCoordY);
            firstBuffer[EntityCoordX * MAP_SIZE_X + EntityCoordY] = '0';
        }
    }

    for (int i = 0; i < MAX_BULLETS; i++)
    {
        if (gm->you->secondGun->getActiveBullet(i) == 1)
        {
            gm->you->secondGun->bullets[i]->getEntityCoord(&EntityCoordX, &EntityCoordY);
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
                setcur(2 * j, i);
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