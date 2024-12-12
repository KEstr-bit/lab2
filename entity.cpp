#include "entity.h"
#include "helper.h"


Entity::Entity(const double cord_x, const double cord_y, const double speed, const int hit_points, const int damage, const textureType texture)
{
    this->damage = damage;
    this->hitPoints = hit_points;
    this->cordX = cord_x;
    this->cordY = cord_y;
    this->speed = speed;
    this->texture = texture;
    viewAngle = 0;
    last_id++;
    size = 1;
    textureX = 0;
    textureY = 0;
}

Entity::Entity()
{
    cordX = 8;
    cordY = 1;
    hitPoints = 100;
    speed = 1;
    damage = 50;
    viewAngle = 0;
    last_id++;
    size = 1;
    texture = Enemy1;
    textureX = 0;
    textureY = 0;
}

bool Entity::isfriendly()
{
    return friendly;
}


float Entity::getTextureX() const
{
    return textureX;
}

float Entity::getTextureY() const
{
    return textureY;
}

bool Entity::getEntityCord(double* cord_x, double* cord_y) const
{
    *cord_x = this->cordX;
    *cord_y = this->cordY;
    return hitPoints <= 0;
}

bool Entity::getEntityCord(int* cord_x, int* cord_y)
{
    *cord_x = helper::myRound(this->cordX);
    *cord_y = helper::myRound(this->cordY);
    return hitPoints <= 0;
}

int Entity::getEntityDamage()
{
    return damage;
}

int Entity::getEntityHitPoints()
{
    return hitPoints;
}

double Entity::getEntityAngle()
{
    return viewAngle;
}

void Entity::attackEntity(const int damage)
{
    hitPoints -= damage;
    eventFl = true;
    if (this->isAlive())
    {
        if (textureY != 3)
        {
            textureY = 3;
            textureX = 0;
        }
    } else if(textureY != 1)
    {
        textureY = 1;
        textureX = 0;
    }
}

bool Entity::isAlive()
{
    return hitPoints >= 0.1;
}

bool Entity::entityStep()
{
    cordX += helper::projectionToX(speed, helper::degToRad(viewAngle));
    cordY += helper::projectionToY(speed, helper::degToRad(viewAngle));
    return hitPoints <= 0;
}

bool Entity::entityStep(double len)
{
    cordX += helper::projectionToX(len, helper::degToRad(viewAngle));
    cordY += helper::projectionToY(len, helper::degToRad(viewAngle));
    return hitPoints <= 0;
}

bool Entity::entityMapStep(GameMap* map)
{
    double oldX, oldY;
    this->getEntityCord(&oldX, &oldY);

    double sdeltaX = size/2;
    double sdeltaY = sdeltaX;

    this->entityStep();

    double deltaX = this->cordX - oldX;
    if (deltaX < 0)
        sdeltaX *= -1;

    double deltaY = this->cordY - oldY;
    if (deltaY < 0)
        sdeltaY *= -1;


    //если объект шагнул в стену
    if (map->isWall(this->cordX + sdeltaX, this->cordY))
    {
        if (map->isWall(this->cordX, this->cordY + sdeltaY))
        {
            this->cordX = oldX;
            this->cordY = oldY;
        }
        else
        {
            this->cordX = oldX;
            this->cordY = oldY + deltaY;
        }
        return true;
    }
    else
    {
        if (map->isWall(this->cordX, this->cordY + sdeltaY))
        {
            this->cordX = oldX + deltaX;
            this->cordY = oldY;
            return true;
        }

    }

    return false;
}

void Entity::Step(GameMap* map, double angle)
{
    double buf = viewAngle;
    viewAngle = angle;
    entityMapStep(map);
    viewAngle = buf;
}

bool Entity::frameShift()
{
	textureX+= FRAME_SPEED;
	if (helper::myRound(textureX) >= TexturePack::FRAMES_COUNT)
	{
		textureX = 0;
		textureY = 0;
		eventFl = false;
		return true;
	}
	return false;
}


double Entity::getSize()
{
    return size;
}

textureType Entity::getTextureType()
{
    return texture;
}
