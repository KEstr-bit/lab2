#pragma once
#include "bullet.h"
#include "helper.h"

class weapon
{
protected:
    int bulletCount;                    //���������� ����, ����������� �� ���
    double bulletSpeed;                       //�������� ������ ����
    int bulletDamage;                         //����, �������� �����
    int activeBullets[10];              //������, ������������ ����
    int countActiveBullets;
public:
    bullet* bullets[MAX_BULLETS];         //������ ����

public:
    weapon(int bullet_Count, double bullet_Speed, int bullet_Damage);
    weapon();
    ~weapon();
    //������� �������������� ������
    int getCountActiveBullets();
    int setActiveBullet(int index, int active);
    int getActiveBullet(int index);
    int changeCountActiveBullets(int change);
    int allBulletMovment();

};