#include "Game.h"

#include "Archer.h"
#include "Bomber.h"
#include "Bullet.h"
#include "Necromancer.h"
#include "QuadTree.h"
Game::Game(): texture_pack(nullptr)
{
	player = new Player(7, 1);

	try
	{
		texture_pack = new TexturePack();
	}
	catch (std::exception)
	{
		delete texture_pack;
		texture_pack = new TexturePack(1);
	}

	entities.emplace_back(new Necromancer(2, 7, player));
	entities.emplace_back(new Bomber(1, 5, player));
	entities.emplace_back(new Archer(1, 2, player));
}

Game::~Game()
{
    delete player;
    delete texture_pack;
    entities.clear();
}


void Game::allEntityMovement(GameMap& map)
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
    player->update(map, newEntities);
    entities.insert(entities.end(), newEntities.begin(), newEntities.end());
}


Entity* Game::getEntityByIndex(const int index) const
{
    return entities.at(index);
}

void Game::playerShot()
{
    player->shot(entities);
}

int Game::getCountEntity() const
{
    return static_cast<int>(entities.size());
}

void Game::interaction(GameMap& map)
{
    this->allEntityMovement(map);                        //движение всех лбъектов

    QuadTree<Entity*> quadTree(0, 0, 0, GameMap::MAP_SIZE_X, GameMap::MAP_SIZE_Y);

    for (const auto it : entities)
    {
        quadTree.insert(it);
    }

    quadTree.insert(player);

    for (const auto it : entities)
    {
        if (!it->isAlive())
            continue;

        std::vector<Entity*> potentialCollisions = quadTree.retrieve(it);

        for (const auto& potentialCollision : potentialCollisions)
        {

            if (!potentialCollision->isAlive())
                continue;

            if (it == potentialCollision)
                continue;

            if (!it->intersects(*potentialCollision, 0.7f))
                continue;

            if (const auto b = dynamic_cast<Bullet*>(it))
            {
                if (b->isFriendly() != potentialCollision->isFriendly())
                {
                    potentialCollision->dealDamage(b->getDamage());
                    b->kill();
                    break;
                }
            }

            if (const auto e = dynamic_cast<Enemy*>(it))
            {
                if (dynamic_cast<Bullet*>(potentialCollision))
                    continue;

                double x, y;
                potentialCollision->getCords(x, y);
                double cordX, cordY;
                e->getCords(cordX, cordY);

                const double distance = Helper::calcDistance(cordX, cordY, x, y);
                double angle = Helper::radToDeg(acos((cordX - x) / distance));

                if ((cordY - y) / distance < 0)
                    angle *= -1;

                e->directionStep(map, angle);

            }
        }
    }
}
