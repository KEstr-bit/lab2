#pragma once
#include "Entity.h"

class Bullet : public Entity
{

public:
    
    Bullet(double coordX, double coordY, double flightAngle, int damage, double speed, textureType texture);
    Bullet(double coordX, double coordY, double flightAngle, int damage, double speed);
    Bullet(double coordX, double coordY, double flightAngle, int damage, double speed, bool friendly);
    Bullet(Bullet*);
    Bullet();
    ~Bullet();

    //движение пули
    bool update(GameMap* map, std::vector<Entity*>& entities) override;
    //установка оставшейся длины
    void setRemLen(double len);
    
    //сложение угла полета, урона и скорости двух пуль
    Bullet operator+(const Bullet& other) const {
        return Bullet(this->cordX, this->cordY, this->viewAngle + other.viewAngle, this->damage + other.damage, this->speed + other.speed);
    }
};