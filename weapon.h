#pragma once
#include "bullet.h"
#include "helper.h"
#include <vector>

class weapon
{
protected:
    int bulletCount;                    //���������� ����, ����������� �� ���
    double bulletSpeed;                 //�������� ������ ����
    int bulletDamage;                   //����, �������� �����

public:


public:
    virtual int shot(double coordX, double coordY, double shotAngle, std::vector<bullet>& bullets) = 0;
    weapon(int bulletCount, double bulletSpeed, int bulletDamage);
    weapon();
    ~weapon();

};