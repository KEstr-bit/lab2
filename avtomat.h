#pragma once
#include "weapon.h"

class avtomat : public weapon
{
public:
    //��������������� ��������
    int shot(double coordX, double coordY, double shotAngle, std::map<int, entity*> &entiyes) override;
};
