#pragma once
#include "enemy.h"

class Necromant : public enemy
{
public:
	Necromant(double coordX, double coordY, double speed, int hitPoints, int damage, Player* player);
	Necromant(Player* player);
	bool update(GameMap* map, std::vector<Entity*>& entities) override;
	void respawn(GameMap* map, std::vector<Entity*>& entities);
	~Necromant();

private:
	shotGun* avt;


};
