#pragma once
#include "player.h"
#include "enemy.h"

class game
{
public:
    game();
    ~game();
    //движение игрока
    int gamePlayerStep(СardinalDirections rot);
    //взаимодействие объектов
    int interaction();
    //вывод текущего состояния игры
    int vivod();

public:
    int Map_Size_X;         //Размер карты по X
    int Map_Size_Y;         //Размер карты по Y
    char* map;              //карта
    player* you;            //игрок
    enemy* monster;         //враг
};