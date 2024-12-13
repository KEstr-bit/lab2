#pragma once
#include "Enemy.h"

class Bomber : public Enemy
{
public:
	Bomber(double cordX, double cordY, Entity* target);
	bool update(GameMap& map, std::vector<Entity*>& entities) override;
};
