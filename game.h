#pragma once
#include "player.h"
#include "enemy.h"

#define MAX_X 10
#define MAX_Y 10

class game
{
private:
    int Map_Size_X;         //������ ����� �� X
    int Map_Size_Y;         //������ ����� �� Y
    char* map;              //�����
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
    int getWorldMap(char getMap[MAX_X][MAX_Y]);
    
};