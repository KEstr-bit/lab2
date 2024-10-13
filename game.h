#pragma once
#include "player.h"
#include "enemy.h"

class game
{
public:
    game();
    ~game();
    //движение игрока
    int gamePlayerStep(int rot);
    //взаимодействие объектов
    int interaction();
    //вывод текущего состо€ни€ игры
    int vivod();
    //получение данных о здоровье игрока
    int getGamePlayerHitPoints();
    //получение данных о здоровье врага
    int getGameEnemyHitPoints();


public:
    int Map_Size_X;         //–азмер карты по X
    int Map_Size_Y;         //–азмер карты по Y
    char* map;              //карта
    player* you;            //игрок
    enemy* monster;         //враг
};