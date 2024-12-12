#include "Game.h"

#include "Archer.h"
#include "Bomber.h"
#include "Bullet.h"
#include "Necromant.h"
#include "QuadTree.h"
Game::Game()
{
    you = new Player();

    try {
        tPack = new TexturePack();
    }
    catch (std::exception) {
        delete tPack;
        tPack = new TexturePack(1);
    }

    entities.emplace_back(new Necromant(you));
    entities.emplace_back(new Bomber(1, 5, 0.06, 100, 200, you));
    entities.emplace_back(new Archer(1, 2, 0.03, 100, 50, you));

    Bullet bul1;
    Bullet bul2;

    entities.emplace_back(new Bullet(bul1 + bul2));
}

Game::~Game()
{
}


void Game::allEntityMovment(GameMap* map)
{
    std::vector<Entity*> newEntities;
    for (auto it = entities.begin(); it != entities.end(); )
    {
	    
        //если entity больше не может двигаться
        if ((*it)->update(map, newEntities))
        {
            delete *it;
            it = entities.erase(it);
        }
        else ++it;
    }
    you->update(map, newEntities);
    entities.insert(entities.end(), newEntities.begin(), newEntities.end());
}


Entity* Game::getEntityByIndex(int index)
{

    return entities.at(index);
}

void Game::playerShot()
{
    you->shot(entities);
}

int Game::getCountEntity()
{
    return entities.size();
}

void Game::interaction(GameMap* map)
{
    this->allEntityMovment(map);                        //движение всех лбъектов

    int monsterCoordX, monsterCoordY;                   //координаты врагов

    QuadTree<Entity*> quadTree(0, 0, 0, GameMap::MAPSIZEX, GameMap::MAPSIZEY);

    for (auto it : entities)
    {
        quadTree.insert(it);
    }

    quadTree.insert(you);

    for (auto it : entities)
    {
        if (!it->isAlive())
            continue;

        std::vector<Entity*> potentialCollisions = quadTree.retrieve(it);

        for (auto& potentialCollision : potentialCollisions)
        {

            if(!potentialCollision->isAlive())
                continue;

            if (it == potentialCollision)
                continue;

            if (!it->intersects(potentialCollision, 0.7))
                continue;

            if (Bullet* b = dynamic_cast<Bullet*>(it))
            {
	            if(b->isfriendly() != potentialCollision->isfriendly())
	            {
                    potentialCollision->attackEntity(b->getEntityDamage());
                    b->setRemLen(0);
                    break;
                }
            }

            if (Enemy* e = dynamic_cast<Enemy*>(it))
            {
                if (Bullet* pce = dynamic_cast<Bullet*>(potentialCollision))
					continue;

                    double x, y;
                    potentialCollision->getEntityCord(&x, &y);
                    double cord_x_, cord_y_;
                    e->getEntityCord(&cord_x_, &cord_y_);

                    double distance = Helper::calcDistance(cord_x_, cord_y_, x, y);
                    double angle = Helper::radToDeg(acos((cord_x_ - x) / distance));

                    if ((cord_y_ - y) / distance < 0)
                        angle *= -1;

                    e->Step(map, angle);
                
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
        if (Enemy* e = dynamic_cast<Enemy*>(it->second)) 
        {
            //запись id врага в monstersMap по координатам
            e->getEntityCord(&monsterCoordX, &monsterCoordY);
            monstersMap[monsterCoordX][monsterCoordY] = it->first;
        }
    }

    int playerCoordX, playerCoordY;
    int id = -1;

    //проверка столкновения игрока с врагом
    if (!this->you->getEntityCord(&playerCoordX, &playerCoordY))
        id = monstersMap[playerCoordX][playerCoordY];

    if (id != -1)
    {
        Entity* e = this->findEntityByID(id);
        this->you->attackEntity(e->getEntityDamage());
    }

    //перебор пуль
    for (auto it = entities.begin(); it != entities.end(); it++)
    {
        if (Bullet* b = dynamic_cast<Bullet*>(it->second))
        {
            int bulletCoordX, bulletCoordY;

            b->getEntityCord(&bulletCoordX, &bulletCoordY);

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

