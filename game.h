#pragma once
#include "Player.h"
#include "Enemy.h"

class Game
{
public:
    Player* player;                     //игрок
    TexturePack* texture_pack;          //хранилище текстур
private:
    std::vector<Entity*> entities;      //вектор объектов
public:
    Game();
    ~Game();
    void interaction(GameMap& map);
    void playerShot();
    Entity* getEntityByIndex(int index) const;
    int getCountEntity() const;
    
protected:
    void allEntityMovement(GameMap& map);

};


