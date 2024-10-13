#pragma once
#include "player.h"
#include "enemy.h"

#define MAX_X 10
#define MAX_Y 10

class game
{
private:
    int mapSizeX;         //Размер карты по X
    int mapSizeY;         //Размер карты по Y
    char* worldMap;              //карта
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
    int getWorldMap(char get_Map[MAX_X][MAX_Y]);
    
};