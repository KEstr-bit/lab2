#pragma once
#include "player.h"
#include "enemy.h"

#define MAX_X 10
#define MAX_Y 10

class game
{
private:
    int Map_Size_X;         //Размер карты по X
    int Map_Size_Y;         //Размер карты по Y
    char* map;              //карта
public:
    player* you;            //игрок
    enemy* monster;

public:
    game();
    ~game();

    //взаимодействие объектов
    int interaction();
    //вывод текущего состояния игры
    int vivod();
    int getMapSizeX();
    int getWorldMap(char getMap[MAX_X][MAX_Y]);
    
};