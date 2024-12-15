#include "Entity.h"
#include "Helper.h"


Entity::Entity(const double cordX, const double cordY, const double speed, const double hitPoints, const double damage,
               const double size, const TextureType texture, const bool friendly):
	texture(texture),
	size(size)
{
    this->cordX = cordX;
    this->cordY = cordY;
    this->speed = speed;
	this->damage = damage;
	this->hitPoints = hitPoints;
    this->friendly = friendly;
}


bool Entity::isFriendly() const
{
    return friendly;
}


void Entity::getCords(double& cordX, double& cordY) const
{
    cordX = this->cordX;
    cordY = this->cordY;
}

void Entity::getCords(int& cordX, int& cordY) const
{
    cordX = static_cast<int>(Helper::round(this->cordX));
    cordY = static_cast<int>(Helper::round(this->cordY));
}

double Entity::getSpeed() const
{
    return damage;
}

double Entity::getDamage() const
{
    return damage;
}

double Entity::getHitPoints() const
{
    return hitPoints;
}

double Entity::getAngle() const
{
    return viewAngle;
}

void Entity::dealDamage(const double damage)
{
    hitPoints -= damage;
    if (isAlive())
	    startAnimation(ANIM_TAKING_DAMAGE, 1);
    else if(animation != ANIM_DIE)
	    startAnimation(ANIM_DIE);
}

void Entity::kill()
{
    hitPoints = 0;
    startAnimation(ANIM_DIE);
}

bool Entity::isAlive() const
{
    return hitPoints > 0.1;
}

void Entity::baseStep()
{
    cordX += Helper::projectToX(speed, Helper::degToRad(viewAngle));
    cordY += Helper::projectToY(speed, Helper::degToRad(viewAngle));
}


bool Entity::move(GameMap& map)
{
    double oldX, oldY;
    this->getCords(oldX, oldY);

    double sizeShiftX = size / 2;
    double sizeShiftY = sizeShiftX;

    this->baseStep();

    const double deltaX = this->cordX - oldX;
    if (deltaX < 0)
        sizeShiftX *= -1;

    const double deltaY = this->cordY - oldY;
    if (deltaY < 0)
        sizeShiftY *= -1;


    //если объект шагнул в стену
    if (map.isWall(this->cordX + sizeShiftX, this->cordY))
    {
        if (map.isWall(this->cordX, this->cordY + sizeShiftY))
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
        if (map.isWall(this->cordX, this->cordY + sizeShiftY))
        {
            this->cordX = oldX + deltaX;
            this->cordY = oldY;
            return true;
        }

    }

    return false;
}

bool Entity::directionStep(GameMap& map, const double angle)
{
	const double oldAngle = viewAngle;
    viewAngle = angle;
	const bool fl = move(map);
    viewAngle = oldAngle;
    return fl;
}

bool Entity::intersects(const Entity& other, const float coefficient) const
{
	const double distance = Helper::calcDistance(cordX, cordY, other.cordX, other.cordY);
	return distance < (size + other.size) * coefficient / 2;
}

void Entity::startAnimation(const Animations animation)
{
    frame = 0;
    this->animation = animation;
    eventFl = true;
}

void Entity::getAnimationState(Animations& animation, int& frame)
{
    frame = static_cast<int>(Helper::round(this->frame));
    animation = this->animation;
}

void Entity::updateAnimation()
{
    frame += FRAME_SPEED;
    if (Helper::round(frame) >= TexturePack::FRAMES_COUNT)
    {
        frame = 0;
        animation = ANIM_BASE;
        eventFl = false;
    }
}

void Entity::startAnimation(const Animations animation, int)
{
    frame = 0;
	this->animation = animation;
}