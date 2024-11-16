#pragma once
#include "entity.h"
#include "shotGun.h"
#include "avtomat.h"
#include "helper.h"

class player : public entity
{
private:
    WeaponOption activeWeapon;  //�������� ������

public:
    static const int VISION_SPEED = 1;  //�������� ��������� ���� ������
    static const int FOV = 60;          //������ ������
    shotGun* firstGun;                  //������ ������1
    avtomat* secondGun;                 //������ ������2

public:
    player(double coordX, double coordY, double speed, int hitPoints, int damage);
    player();
    ~player();
    //���������� ������
    bool playerMapStep(�ardinalDirections step_Direction, GameMap* map);
    //������� ���� ������
    void changeVision(�ardinalDirections direct_pl);
    //����� ������
    int changeActiveWeapon();
    //������� 
    int shot(std::map<int, entity*> &entiyes);

    bool entityMovment(GameMap* map, double playerX, double playerY) override;
};
