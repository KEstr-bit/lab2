#pragma once
#include "player.h"
#include "enemy.h"

#define MAX_X 10
#define MAX_Y 10

class game
{
private:
    int mapSizeX;         //������ ����� �� X
    int mapSizeY;         //������ ����� �� Y
    char* worldMap;              //�����
public:
    player* you;            //�����
    enemy* monster;

public:
    game();
    ~game();

    //�������������� ��������
    int interaction();
    //����� �������� ��������� ����
    int vivod();
    int getMapSizeX();
    int getWorldMap(char get_Map[MAX_X][MAX_Y]);
    
};