#pragma once
#include "player.h"
#include "enemy.h"
#include "GameMap.h"
#include <vector>
#include <map>
#include "TexturePack.h"

#define MAX_X 10
#define MAX_Y 10

class game
{
public:
    player* you;            //игрок
    TexturePack* tPack;
private:
    std::map<int, entity*> entities;
public:
    game();
    ~game();
    //взаимодействие объектов
    entity* findEntityByID(int id);
    entity* getEntityByIndex(int index);
    void playerShot();
    int getCountEntity();
    int interaction(GameMap* map);
    int allEntityMovment(GameMap* map);
};