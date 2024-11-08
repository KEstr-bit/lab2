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

int game::allBulletMovment(GameMap* map)
{
    for (int i = 0; i < bullets.size(); i++)
    {
        if(bullets[i].bulletMapStep(map))
            bullets.erase(bullets.begin() + i);
    }
    return 0;
}

int game::interaction(GameMap* map)
{
    this->allBulletMovment(map);                    //�������� ����

    bool monsterIsAlive = false;
    int monsterCoordX, monsterCoordY;
    if (!monster->getEntityCoord(&monsterCoordX, &monsterCoordY))
    {
        monsterIsAlive = true;
    }

    int playerCoordX, playerCoordY;
    if (!you->getEntityCoord(&playerCoordX, &playerCoordY) && monsterIsAlive)
    {
        this->monster->enemyMovment(map, playerCoordX, playerCoordY);     //�������� �����
        //���� ���� ������ ������
        if (monsterCoordX == playerCoordX && monsterCoordY == playerCoordY)
        {
            you->attackEntity(monster->getEntityDamage());
        }
    }

    //���� �� ����� ���� ����
    for (int i = 0; i < bullets.size(); i++)
    {
        int bulletCoordX, bulletCoordY;

        bullets[i].getEntityCoord(&bulletCoordX, &bulletCoordY);

        if (bulletCoordX == monsterCoordX && bulletCoordY == monsterCoordY && monsterIsAlive)
        {
            monster->attackEntity(bullets[i].getEntityDamage());
            bullets.erase(bullets.begin() + i);
        }
    }
        

    return 0;
}
