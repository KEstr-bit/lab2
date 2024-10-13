#pragma once
#include "bullet.h"
#include "helper.h"

class weapon
{
protected:
    int bulletCount;                    //���������� ����, ����������� �� ���
    double speed;                       //�������� ������ ����
    int damage;                         //����, �������� �����
    int activeBullets[10];              //������, ������������ ����
    int countActiveBullets;
public:
    bullet* bulls[MAX_BULLETS];         //������ ����

public:
    weapon(int bc, double sp, int dm);
    weapon();
    ~weapon();
    //������� �������������� ������
    int getWeaponCountBullets();
    int setActiveBullet(int index, int active);
    int getActiveBullet(int index);
    int changeCountActiveBullets(int change);
    int allBulletMovment();

};