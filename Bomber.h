#pragma once
#include "enemy.h"

class Bomber : public enemy
{
public:
	Bomber(double coordX, double coordY, double speed, int hitPoints, int damage, Player* player);
	Bomber(Player* player);
	bool update(GameMap* map, std::vector<Entity*>& entities) override;
	~Bomber();


};
