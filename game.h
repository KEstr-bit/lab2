#pragma once
#include "Player.h"
#include "Enemy.h"
#include "Helper.h"

#define MAX_X 10
#define MAX_Y 10

class Game
{
public:
    Player* you;            //игрок
    TexturePack* tPack;     //хранилище текстур
private:
    std::vector<Entity*> entities;    //вектор объектов
public:
    Game();
    ~Game();
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
    Game& operator++() {
        double x, y, a;
        a = you->getEntityAngle();
        you->getEntityCord(&x, &y);

        x += 2 * cos(Helper::degToRad(a));
        y += 2 * sin(Helper::degToRad(a));

        entities.emplace_back(new Enemy(x, y, 0.01, 100, 10, you));
        return *this;
    }

    Game operator++(int) {
        Game temp = *this;  
        ++(*this);       
        return temp;       
    }
};


