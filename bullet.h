#pragma once
#include "entity.h"

class bullet : public entity
{
public:
    bullet(double coordX, double coordY, double flightAngle, int damage, double speed);
    bullet();
    ~bullet();
    //движение пули
    bool bulletMapStep(GameMap* map);
private:
    double remainLen;
};