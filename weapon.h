#pragma once
#include <map>
#include "entity.h"

class weapon
{
protected:
    int bulletCount;                    //���������� ����, ����������� �� ���
    double bulletSpeed;                 //�������� ������ ����
    int bulletDamage;                   //����, �������� �����

public:
    weapon(int bulletCount, double bulletSpeed, int bulletDamage);
    weapon();
    ~weapon();

    //������� �� ������
    virtual int shot(double coordX, double coordY, double shotAngle, std::map<int, entity*>& entiyes) = 0;

};