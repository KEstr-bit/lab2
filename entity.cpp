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
	    startAnimation(ANIM_TAKING_DAMAGE);
    else if(animation != ANIM_DIE)
	    startAnimation(ANIM_DIE);
}

void Entity::kill()
{
    hitPoints = 0;
    startAnimation(ANIM_DIE);
}

bool Entity::update(GameMap& map, std::vector<Entity*>& entities)
{
    updateAnimation();
    if (eventFl)
        return false;
    if (!isAlive())
        return true;

    return false;
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

void Entity::baseStep(const double len)
{
    cordX += Helper::projectToX(speed + len, Helper::degToRad(viewAngle));
    cordY += Helper::projectToY(speed + len, Helper::degToRad(viewAngle));
}

bool Entity::mapStep(GameMap& map)
{
    double oldX, oldY;
    this->getCords(oldX, oldY);

    double sdeltaX = size / 2;
    double sdeltaY = sdeltaX;

    this->baseStep();

    double deltaX = this->cordX - oldX;
    if (deltaX < 0)
        sdeltaX *= -1;

    double deltaY = this->cordY - oldY;
    if (deltaY < 0)
        sdeltaY *= -1;


    //если объект шагнул в стену
    if (map.isWall(this->cordX + sdeltaX, this->cordY))
    {
        if (map.isWall(this->cordX, this->cordY + sdeltaY))
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
        if (map.isWall(this->cordX, this->cordY + sdeltaY))
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
	const bool fl = mapStep(map);
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