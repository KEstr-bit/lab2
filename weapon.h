#pragma once
#include "bullet.h"
#include "helper.h"

class weapon
{
protected:
    int bulletCount;    //���������� ����, ����������� �� ���
    double speed;       //�������� ������ ����
    int damage;         //����, �������� �����
    int type;           //��� ������: 0 - ��������, 1 - �������
    int activeBullets[10];              //������, ������������ ����
    �ardinalDirections playerRotation;  //����������� ������� ������
    int countActiveBullets;
public:
    bullet* bulls[MAX_BULLETS];         //������ ����

public:
    weapon(int bc, double sp, int tp, int dm);
    weapon();
    ~weapon();
    //������� �������������� ������
    int getWeaponStat(int* bc, double* sp, int* dm, int* t);
    int getWeaponCountBullets();
    int setActiveBullet(int index, int active);
    int getActiveBullet(int index);
    int changeCountActiveBullets(int change);
    int allBulletMovment();

};