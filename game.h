#pragma once
#include "player.h"
#include "enemy.h"
#include "helper.h"

#define MAX_X 10
#define MAX_Y 10

class game
{
public:
    Player* you;            //игрок
    TexturePack* tPack;     //хранилище текстур
private:
    std::map<int, Entity*> entities;    //вектор объектов
public:
    game();
    ~game();
    //поиск entity по id
    Entity* findEntityByID(int id);
    //получение entity по индексу
    Entity* getEntityByIndex(int index);
    //выстрел игрока
    void playerShot();
    int getCountEntity();
    //взаимодействие объектов
    void interaction(GameMap* map);
    //движение всех объектов
    void allEntityMovment(GameMap* map);

    //спавн врага по взгляду игрока на расстоянии 2м
    game& operator++() {
        double x, y, a;
        a = you->getEntityAngle();
        you->getEntityCoord(&x, &y);

        x += 2 * cos(helper::degToRad(a));
        y += 2 * sin(helper::degToRad(a));

        entities.emplace(Entity::lastID, new enemy(x, y, 0.01, 100, 10, you));
        return *this;
    }

    game operator++(int) {
        game temp = *this;  
        ++(*this);       
        return temp;       
    }
};


