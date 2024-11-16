#include "game.h"
#include "bullet.h"

game::game()
{
    you = new player();
    tPack = new TexturePack();
    entities.emplace(entity::lastID, new enemy());
    entities.emplace(entity::lastID, new enemy(1, 5, 0.01, 100, 50));

    bullet bul1;
    bullet bul2;

    entities.emplace(entity::lastID, new bullet(bul1 + bul2));


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
        //если entity больше не может двигаться
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
    this->allEntityMovment(map);                    //движение всех лбъектов

    int monsterCoordX, monsterCoordY;               //координаты врагов
    int monstersMap[map->MAPSIZEX][map->MAPSIZEY];  //карта id врагов

    for (int i = map->MAPSIZEX * map->MAPSIZEY - 1; i >= 0; i--)
    {
        *(monstersMap[0] + i) = -1;
    }

    for (auto it = entities.begin(); it != entities.end(); it++) {
        // Пробуем выполнить динамическое приведение
        if (enemy* e = dynamic_cast<enemy*>(it->second)) 
        {
            //запись id врага в monstersMap по координатам
            e->getEntityCoord(&monsterCoordX, &monsterCoordY);
            monstersMap[monsterCoordX][monsterCoordY] = it->first;
        }
    }

    int playerCoordX, playerCoordY;
    int id = -1;

    //проверка столкновения игрока с врагом
    if (!this->you->getEntityCoord(&playerCoordX, &playerCoordY))
        id = monstersMap[playerCoordX][playerCoordY];

    if (id != -1)
    {
        entity* e = this->findEntityByID(id);
        this->you->attackEntity(e->getEntityDamage());
    }

    //перебор пуль
    for (auto it = entities.begin(); it != entities.end(); it++)
    {
        if (bullet* b = dynamic_cast<bullet*>(it->second))
        {
            int bulletCoordX, bulletCoordY;

            b->getEntityCoord(&bulletCoordX, &bulletCoordY);

            //провекра столкновения пули с врагом
            int id = monstersMap[bulletCoordX][bulletCoordY];

            if (id == -1)
                continue;

            //поиск врага по id
            entity* e = this->findEntityByID(id);

            //нанесение урона врагу
            e->attackEntity(b->getEntityDamage());

            b->setRemLen(0);
            break;
        }

    }

    return 0;
}
