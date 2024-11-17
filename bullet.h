#pragma once
#include "entity.h"

class bullet : public entity
{
private:
    double remainLen;   //оставшаяся длина пути

public:
    bullet(double coordX, double coordY, double flightAngle, int damage, double speed, textureType texture);
    bullet(double coordX, double coordY, double flightAngle, int damage, double speed);
    bullet(bullet*);
    bullet();
    ~bullet();

    //движение пули
    bool entityMovment(GameMap* map, double playerX, double playerY) override;
    //установка оставшейся длины
    void setRemLen(double len);

    //сложение угла полета, урона и скорости двух пуль
    bullet operator+(const bullet& other) const {
        return bullet(this->coordX, this->coordY, this->viewAngle + other.viewAngle, this->damage + other.damage, this->speed + other.speed);
    }
};