#pragma once
#include "entity.h"

class bullet : public Entity
{

public:
    
    bullet(double coordX, double coordY, double flightAngle, int damage, double speed, textureType texture);
    bullet(double coordX, double coordY, double flightAngle, int damage, double speed);
    bullet(double coordX, double coordY, double flightAngle, int damage, double speed, bool friendly);
    bullet(bullet*);
    bullet();
    ~bullet();

    //движение пули
    bool update(GameMap* map, std::vector<Entity*>& entities) override;
    //установка оставшейся длины
    void setRemLen(double len);
    
    //сложение угла полета, урона и скорости двух пуль
    bullet operator+(const bullet& other) const {
        return bullet(this->cordX, this->cordY, this->viewAngle + other.viewAngle, this->damage + other.damage, this->speed + other.speed);
    }
};