#pragma once
#include "Enemy.h"

class Archer final: public Enemy
{
private:
	Rifle* rifle;
public:
	Archer(double cordX, double cordY, Entity* target);
	~Archer();
	bool update(GameMap& map, std::vector<Entity*>& entities) override;


    
};