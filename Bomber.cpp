#include "Bomber.h"

Bomber::Bomber(const double cordX, const double cordY, Entity* target): Enemy(
	cordX, cordY, 0.06, 50, 100, 1, ENEMY, target){}


bool Bomber::update(GameMap& map, std::vector<Entity*>& entities)
{
    updateAngle();
	switch (animation)
	{
	case ANIM_MOVE: 
        mapStep(map);
		break;
	case ANIM_ATTACK1:
        if(frame == 7.0f && intersects(*target, 1))
        {
            target->dealDamage(damage);
            kill();
        }
		break;
    default: 
        break;
	}

    if (Entity::update(map, entities))
        return true;

    if (eventFl)
        return false;

    //если враг не видит цель
    if (!isTargetSeen(map)){
        return false;
    }

    if (intersects(*target, 0.7f)) {
        startAnimation(ANIM_ATTACK1);
        return false;
    }

    startAnimation(ANIM_MOVE);
    return false;
}

