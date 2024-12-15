#pragma once
#include "Enemy.h"
#include "ShotGun.h"

class Necromancer final: public Enemy
{
public:
	Necromancer(double cordX, double cordY, Entity* target);
	~Necromancer();
	bool update(GameMap& map, std::vector<Entity*>& entities) override;
	void respawn(GameMap& map, std::vector<Entity*>& entities);
	

private:
	ShotGun* shotGun;


};
