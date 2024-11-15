#pragma once
#include "player.h"
#include "enemy.h"
#include "helper.h"

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

    game& operator++() {
        double x, y, a;
        a = you->getEntityAngle();
        you->getEntityCoord(&x, &y);

        x += 2 * cos(degToRad(a));
        y += 2 * sin(degToRad(a));

        entities.emplace(entity::lastID, new enemy(x, y, 0.01, 100, 10));
        return *this;
    }

    game operator++(int) {
        game temp = *this;  
        ++(*this);       
        return temp;       
    }



    friend bool isEnd(game* gm);
};


