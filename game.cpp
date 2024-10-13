#include <iostream>
#include "game.h"
#include "entity.h"
#include "player.h"
#include "enemy.h"
#include "helper.h"

game::game()
{
    Map_Size_X = MAX_X;
    Map_Size_Y = MAX_Y;
    map = (char*)calloc(Map_Size_X * Map_Size_Y, sizeof(char));
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
    for (int x = 0; x < Map_Size_X; x++)
    {
        for (int y = 0; y < Map_Size_Y; y++)
        {
            *(map + x * Map_Size_X + y) = preMap[x][y];
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
    this->monster->enemyMovment(map, Map_Size_X, you);     //�������� �����
    this->you->gun->allBulletMovment();                    //�������� ����

    int monsterCoordX, monsterCoordY;
    int playerCoordX, playerCoordY;
    monster->getEntityCoord(&monsterCoordX, &monsterCoordY);
    you->getEntityCoord(&playerCoordX, &playerCoordY);

    //���� �� ����� ���� ����
    if (you->gun->getWeaponCountBullets() > 0)
    {
        for (int i = 0; i < 10; i++)
        {
            //���� ���� ����������
            if (you->gun->getActiveBullet(i) == 1)
            {
                
                int bulletCoordX, bulletCoordY;
                int bulletFinalCoordX, bulletFinalCoordY;

                you->gun->bulls[i]->getBulletCoords(&bulletFinalCoordX, &bulletFinalCoordY);
                you->gun->bulls[i]->getEntityCoord(&bulletCoordX, &bulletCoordY);
                

                //���� ���� ����������� �� ������
                if (*(map + bulletCoordX * Map_Size_X + bulletCoordY) == '#')
                {
                    delete you->gun->bulls[i];
                    you->gun->setActiveBullet(i, 0);
                    you->gun->changeCountActiveBullets(-1);
                }
                else
                {
                    
                    //���� ���� ������ �� �����

                    if (bulletCoordX == monsterCoordX && bulletCoordY == monsterCoordY)
                    {

                        monster->attackEntity(you->gun->bulls[i]->getEntityDamage());
                        delete you->gun->bulls[i];
                        you->gun->setActiveBullet(i, 0);
                        you->gun->changeCountActiveBullets(-1);

                    }
                    else
                    {
                        //���� ���� �������� ����� �������� �����
                        if (bulletCoordX == bulletFinalCoordX && bulletCoordY == bulletFinalCoordY)
                        {
                            delete you->gun->bulls[i];
                            you->gun->setActiveBullet(i, 0);
                            you->gun->changeCountActiveBullets(-1);
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

    static char* firstBuffer = (char*)calloc(Map_Size_X * Map_Size_Y, sizeof(char));
    static char* SecondBuffer = (char*)calloc(Map_Size_X * Map_Size_Y, sizeof(char));

    if (firstBuffer == NULL || SecondBuffer == NULL)
    {
        return 1;
    }

    //����������� ����� � ������������ ������
    for (int i = 0; i < Map_Size_X; i++)
        for (int j = 0; j < Map_Size_Y; j++)
        {
            firstBuffer[i * Map_Size_X + j] = map[i * Map_Size_X + j];
        }


    //���� ����� �����
    if (you->getEntityHitPoints() > 0)
    {
        �ardinalDirections rotPlayer;
        you->getEntityCoord(&EntityCoordX, &EntityCoordY);
        rotPlayer = you->getPlayerRotation();


        switch (rotPlayer)
        {
            case North: firstBuffer[EntityCoordX * Map_Size_X + EntityCoordY] = 'N'; break;
            case East: firstBuffer[EntityCoordX * Map_Size_X + EntityCoordY] = 'E'; break;
            case South: firstBuffer[EntityCoordX * Map_Size_X + EntityCoordY] = 'S'; break;
            case West: firstBuffer[EntityCoordX * Map_Size_X + EntityCoordY] = 'W'; break;
        }
    }

    //���� ���� �����
    if (monster->getEntityHitPoints() > 0)
    {
        monster->getEntityCoord(&EntityCoordX, &EntityCoordY);

        firstBuffer[EntityCoordX * Map_Size_X + EntityCoordY] = 'M';
    }

    //����������� ����
    for (int i = 0; i < MAX_BULLETS; i++)
    {
        if (you->gun->getActiveBullet(i) == 1)
        {
            you->gun->bulls[i]->getEntityCoord(&EntityCoordX, &EntityCoordY);
            firstBuffer[EntityCoordX * Map_Size_X + EntityCoordY] = '0';
        }
    }

    setcur(0, 0);
    //����� ����� �����
    for (int i = 0; i < Map_Size_X; i++) 
    {
        for (int j = 0; j < Map_Size_Y; j++) 
        {
            if (firstBuffer[i * Map_Size_X + j] != SecondBuffer[i * Map_Size_X + j])
            {
                setcur(2*j, i);
                std::cout << firstBuffer[i * Map_Size_X + j] << " ";
            }
        }
        std::cout << std::endl;
    }

    for (int i = 0; i < Map_Size_X; i++)
        for (int j = 0; j < Map_Size_Y; j++)
        {
            SecondBuffer[i * Map_Size_X + j] = firstBuffer[i * Map_Size_X + j];
        }
    return 0;
}

int game::getWorldMap(char getMap[MAX_X][MAX_Y])
{
    for (int i = 0; i < Map_Size_X; i++)
    {
        for (int j = 0; j < Map_Size_Y; j++)
        {
            getMap[i][j] = *(map + i*Map_Size_X + j);
        }
    }
    return 0;
}

int  game::getMapSizeX()
{
    return Map_Size_X;
}
