#include <iostream>
#include "game.h"
#include "entity.h"
#include "player.h"
#include "enemy.h"
#include "helper.h"
#include <exception> 



game::game()
{
    you = new player();
    tPack = new TexturePack();
    entities.emplace(entity::lastID, new enemy());
    entities.emplace(entity::lastID, new enemy(1, 5, 0.01, 100, 50));

    sf::Texture texture;
    texture.loadFromFile("image.png");
    tPack->addTexture(texture);
    texture.loadFromFile("image1.png");
    tPack->addTexture(texture);
}

game::~game()
{
}


int game::allEntityMovment(GameMap* map)
{
    double playerCoordX, playerCoordY;
    this->you->getEntityCoord(&playerCoordX, &playerCoordY);
    for (auto e = entities.begin(); e != entities.end();)
    {
        if (e->second->entityMovment(map, playerCoordX, playerCoordY))
        {
            delete e->second;
            e = entities.erase(e);
        }
        else ++e;
    }
    return 0;
}

entity* game::findEntityByID(int id)
{
    auto e = entities.find(id);
    if (e == entities.end())
        return nullptr;

    return e->second;
}

entity* game::getEntityByIndex(int index)
{
    if (index >= entities.size())
        return nullptr;

    auto it = entities.begin();
    std::advance(it, index);

    return it->second;
}

void game::playerShot()
{
    you->shot(entities);
}

int game::getCountEntity()
{
    return entities.size();
}

int game::interaction(GameMap* map)
{
    this->allEntityMovment(map);                    //движение пуль

    int monsterCoordX, monsterCoordY;
    int monstersMap[map->MAPSIZEX][map->MAPSIZEY];

    for (int i = map->MAPSIZEX * map->MAPSIZEY - 1; i >= 0; i--)
    {
        *(monstersMap[0] + i) = -1;
    }

    for (auto it = entities.begin(); it != entities.end(); it++) {
        // Пробуем выполнить динамическое приведение
        if (enemy* e = dynamic_cast<enemy*>(it->second)) 
        {
            e->getEntityCoord(&monsterCoordX, &monsterCoordY);
            monstersMap[monsterCoordX][monsterCoordY] = it->first;
        }
    }

    int playerCoordX, playerCoordY;
    int id = -1;

    if (!this->you->getEntityCoord(&playerCoordX, &playerCoordY))
        id = monstersMap[playerCoordX][playerCoordY];

    if (id != -1)
    {
        entity* e = this->findEntityByID(id);
        this->you->attackEntity(e->getEntityDamage());
    }

    //если на карте есть пули
    for (auto it = entities.begin(); it != entities.end(); it++)
    {
        if (bullet* b = dynamic_cast<bullet*>(it->second))
        {
            int bulletCoordX, bulletCoordY;

            b->getEntityCoord(&bulletCoordX, &bulletCoordY);

            int id = monstersMap[bulletCoordX][bulletCoordY];

            if (id == -1)
                continue;

            entity* e = this->findEntityByID(id);

            e->attackEntity(b->getEntityDamage());
            b->setRemLen(0);
            break;
        }

    }

    return 0;
}
