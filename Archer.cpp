#include "Archer.h"

Archer::Archer(const double cordX, const double cordY, Entity* target): Enemy(
	cordX, cordY, 0.02, 100, 50, 1, ENEMY, target)
{
	rifle = new Rifle(10, 1, 0.1, 50, BULLET, false);
}

Archer::~Archer()
{
    delete rifle;
}


bool Archer::update(GameMap& map, std::vector<Entity*>& entities)
{
    static int shift = 0;
    const double distance = updateAngle();
    switch (animation)
    {
    case ANIM_MOVE:
        if (distance > 5)
            mapStep(map);
        else if (distance < 3)
            directionStep(map,viewAngle - 180);
        else
        {
            if (frame == 0.0f)
            {
                if (rand() % 2)
                    shift = -90;
                else
                    shift = 90;
            }

            if (directionStep(map, viewAngle - shift))
                shift *= -1;
        }
        break;
    case ANIM_ATTACK1:
        if (frame == TexturePack::FRAMES_COUNT / 2.0f)
            if (!rifle->shot(cordX, cordY, viewAngle, entities))
                rifle->reloading();
        break;
    default:
        break;
    }

    rifle->updateAnimation();
    if(Entity::update(map, entities))
        return true;

    if (eventFl)
        return false;

    //если враг не видит цель
    if (!isTargetSeen(map)) {
        return false;
    }
    
    if (rand() % 2)
    {
        startAnimation(ANIM_ATTACK1);
        return false;
    }

    startAnimation(ANIM_MOVE);
    return false;
}


