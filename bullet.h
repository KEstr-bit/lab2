#pragma once
#include "Entity.h"

class Bullet : public Entity
{

public:
    
    Bullet(double cordX, double cordY, double flightAngle, double speed, double hitPoints, double damage, TextureType texture, bool friendly);
    //движение пули
    bool update(GameMap& map, std::vector<Entity*>& entities) override;

};