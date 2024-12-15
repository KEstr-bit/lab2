#include "Bomber.h"

Bomber::Bomber(const double cordX, const double cordY, Entity* target): Enemy(
	cordX, cordY, 0.06, 50, 100, 1, ENEMY, target){}




bool Bomber::update(GameMap& map, std::vector<Entity*>& entities)
{
    lookAtTarget(map);
	switch (animation)
	{
	case ANIM_MOVE: 
        move(map);
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

    updateAnimation();

    if (eventFl)
        return false;

    if (!isAlive())
        return true;

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

