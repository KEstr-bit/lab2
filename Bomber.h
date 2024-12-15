#pragma once
#include "Enemy.h"

class Bomber : public Enemy
{
private:
    bool isTargetSeen(GameMap& map) override
    {
        return true;
    }

public:
	Bomber(double cordX, double cordY, Entity* target);
	bool update(GameMap& map, std::vector<Entity*>& entities) override;

    Bomber& operator=(const Enemy& other) {
        if (this == &other) return *this; // Проверка на самоприсваивание

        other.getCords(cordX, cordY);
        this->speed = other.getSpeed();
        this->damage = other.getDamage();
        this->hitPoints = other.getHitPoints();
        this->friendly = other.isFriendly();
        this->target = other.getTarget();

        return *this;
    }
};
