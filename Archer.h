#pragma once
#include "enemy.h"

class Archer : public enemy
{
public:
	Archer(double coordX, double coordY, double speed, int hitPoints, int damage, Player* player);
	Archer(Player* player);
	bool update(GameMap* map, std::vector<Entity*>& entities) override;
	~Archer();

private:
	avtomat* avt;

    
};