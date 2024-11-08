#pragma once
#include "player.h"
#include "enemy.h"
#include "GameMap.h"
#include <vector>

#define MAX_X 10
#define MAX_Y 10

class game
{
public:
    player* you;            //�����
    enemy* monster;
    std::vector<bullet> bullets;

public:
    game();
    ~game();

    //�������������� ��������
    int interaction(GameMap* map);
    int allBulletMovment(GameMap* map);
};