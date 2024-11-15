#pragma once
#include "entity.h"

class bullet : public entity
{
public:
    bullet(double coordX, double coordY, double flightAngle, int damage, double speed, textureType texture);
    bullet(double coordX, double coordY, double flightAngle, int damage, double speed);
    bullet(bullet*);
    bullet();
    ~bullet();
    //движение пули
    bool entityMovment(GameMap* map, double playerX, double playerY) override;
    void setRemLen(double len){remainLen = len;}

    bullet operator+(const bullet& other) const {
        return bullet(this->coordX, this->coordY, this->viewAngle + other.viewAngle, this->damage + other.damage, this->speed + other.speed);
    }
private:
    double remainLen;
};