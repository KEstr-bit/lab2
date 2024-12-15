#pragma once
#include "AnimationControl.h"
#include "TexturePack.h"
#include "GameMap.h"
#include "Helper.h"

class Entity : public AnimationControl
{
public:
    const TextureType texture;
    const double size;
protected:
    double cordX;            
    double cordY;              
    double hitPoints;              
    double damage;                 
    double speed;                  
    double viewAngle = 0;          
    bool friendly;
    bool eventFl = false;
    float frame = 0;
    Animations animation = ANIM_SPAWN;

protected:
    void baseStep();

public:
    Entity(double cordX, double cordY, double speed, double hitPoints, 
        double damage, double size, TextureType texture, bool friendly);

    bool isFriendly() const;
    bool isAlive() const;

    void getCords(int& cordX, int& cordY) const;
    void getCords(double& cordX, double& cordY) const;
    virtual double getDamage() const;
    double getSpeed() const;
    double getHitPoints() const;
    double getAngle() const;

    void startAnimation(Animations animation) override;
    void getAnimationState(Animations& animation, int& frame) override;
    void updateAnimation() override;
    void startAnimation(Animations animation, int);

    bool move(GameMap& map);
    bool directionStep(GameMap& map, double angle);
    void dealDamage(double damage);
    void kill();

    virtual bool update(GameMap& map, std::vector<Entity*>& entities) = 0;

    bool intersects(const Entity& other, float coefficient) const;


};
