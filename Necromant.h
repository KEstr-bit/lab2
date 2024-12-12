#pragma once
#include "Enemy.h"

class Necromant : public Enemy
{
public:
	Necromant(double coordX, double coordY, double speed, int hitPoints, int damage, Player* player);
	Necromant(Player* player);
	bool update(GameMap* map, std::vector<Entity*>& entities) override;
	void respawn(GameMap* map, std::vector<Entity*>& entities);
	~Necromant();

private:
	ShotGun* avt;


};
