#pragma once
#include "player.h"
#include "enemy.h"

class game
{
public:
    game();
    ~game();
    //�������� ������
    int gamePlayerStep(int rot);
    //�������������� ��������
    int interaction();
    //����� �������� ��������� ����
    int vivod();
    //��������� ������ � �������� ������
    int getGamePlayerHitPoints();
    //��������� ������ � �������� �����
    int getGameEnemyHitPoints();


public:
    int Map_Size_X;         //������ ����� �� X
    int Map_Size_Y;         //������ ����� �� Y
    char* map;              //�����
    player* you;            //�����
    enemy* monster;         //����
};