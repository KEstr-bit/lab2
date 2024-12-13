#include "Necromancer.h"

#include "Archer.h"
#include "Bomber.h"

Necromancer::Necromancer(const double cordX, const double cordY, Entity* target): Enemy(
    cordX, cordY, 0.02, 1000, 50, 2, NECROMANCER, target)
{
	shotGun = new ShotGun(10, 3, 0.05, 30, BULLET, false);
}


bool Necromancer::update(GameMap& map, std::vector<Entity*>& entities)
{
    const double distance = updateAngle();
    switch (animation)
    {
    case ANIM_MOVE:
        
        if (distance > 5){
            mapStep(map);
        }
        break;
    case ANIM_ATTACK1:
        if (frame == 7)
            if (!shotGun->shot(cordX, cordY, viewAngle, entities))
                shotGun->reloading();
        break;
    case ANIM_ATTACK2:
        if (frame == TexturePack::FRAMES_COUNT / 2.0f)
            respawn(map, entities);
        break;
    default:
        break;
    }

    shotGun->updateAnimation();
    if (Entity::update(map, entities))
        return true;

    if (eventFl)
        return false;

    //если враг не видит цель
    if (!isTargetSeen(map)) {
        return false;
    }

    if (distance > 5) {
        startAnimation(ANIM_MOVE);
    }

    if(rand()%50 == 0)
    {
        if(rand()%2)
			startAnimation(ANIM_ATTACK1);
        else
			startAnimation(ANIM_ATTACK2);
    }

    return false;
}

void Necromancer::respawn(GameMap& map, std::vector<Entity*>& entities)
{
    double angle = viewAngle;
    angle -= 45;
    for(int i = 0; i < 4; i++)
    {
        angle += 90;
        double x, y;
        x = 2 * cos(Helper::degToRad(angle)) + cordX;
        y = 2 * sin(Helper::degToRad(angle)) + cordY;
        if (!map.isWall(x, y))
        {
	        if(rand()%2)
	        {
                entities.emplace_back(new Bomber(x, y, target));
	        }
            else
            {
                entities.emplace_back(new Archer(x, y, target));
            }
        }
    }
}

Necromancer::~Necromancer()
{
    delete shotGun;
}
