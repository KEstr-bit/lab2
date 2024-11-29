#include "game.h"
#include "bullet.h"
#include "QuadTree.h"
game::game()
{
    you = new player();

    try {
        tPack = new TexturePack();
    }
    catch (std::exception) {
        delete tPack;
        tPack = new TexturePack(1);
    }

    entities.emplace(Entity::lastID, new enemy());
    entities.emplace(Entity::lastID, new enemy(1, 5, 0.01, 100, 50));

    bullet bul1;
    bullet bul2;

    entities.emplace(Entity::lastID, new bullet(bul1 + bul2));
}

game::~game()
{
}


void game::allEntityMovment(GameMap* map)
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
}

Entity* game::findEntityByID(int id)
{
    auto e = entities.find(id);
    if (e == entities.end())
        return nullptr;

    return e->second;
}

Entity* game::getEntityByIndex(int index)
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

void game::interaction(GameMap* map)
{
    this->allEntityMovment(map);                        //движение всех лбъектов

    int monsterCoordX, monsterCoordY;                   //координаты врагов
    
    QuadTree quadTree(0, 0, 0, GameMap::MAPSIZEX, GameMap::MAPSIZEY);

    for (auto it = entities.begin(); it != entities.end(); it++)
    {
        quadTree.insert(it->second);
    }

    for (auto it = entities.begin(); it != entities.end(); it++)
    {
        if (bullet* b = dynamic_cast<bullet*>(it->second))
        {
            std::vector<Entity*> potentialCollisions = quadTree.retrieve(b);
            for (int i = 0; i < potentialCollisions.size(); i++)
            {
                if (b == potentialCollisions[i])
                    continue;

                if (b->intersects(potentialCollisions[i]))
                {
                    potentialCollisions[i]->attackEntity(b->getEntityDamage());
                    b->setRemLen(0);
                    break;
                }
            }
        }
    }
    /*int monstersMap[map->MAPSIZEX][map->MAPSIZEY];      //карта id врагов

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
        Entity* e = this->findEntityByID(id);
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
            try {
                id = monstersMap[bulletCoordX][bulletCoordY];
            }
            catch (std::out_of_range) {
                id = -1;
            }

            if (id == -1)
                continue;

            //поиск врага по id
            Entity* e = this->findEntityByID(id);

            //нанесение урона врагу
            e->attackEntity(b->getEntityDamage());

            b->setRemLen(0);
            break;
        }
    }
    */
}
