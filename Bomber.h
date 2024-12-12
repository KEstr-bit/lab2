#pragma once
#include "Enemy.h"

class Bomber : public Enemy
{
public:
	Bomber(double coordX, double coordY, double speed, int hitPoints, int damage, Player* player);
	Bomber(Player* player);
	bool update(GameMap* map, std::vector<Entity*>& entities) override;
	~Bomber();


};
