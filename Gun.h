#pragma once
#include "AnimationControl.h"
#include "Entity.h"

class Gun: public AnimationControl
{
public:
    const int magazine_capacity;
    const TextureType texture;
    const TextureType bulletTexture;
protected:
    int bulletCount;                    //количество пуль, выпускаемых за раз
    double bulletSpeed;                 //скорость полета пули
    double bulletDamage;                   //урон, наносимы пулей
    int ammunition = magazine_capacity;
    bool friendly;
    bool eventFl = true;
    float frame = 0;
    Animations animation = ANIM_SPAWN;

public:
    Gun(int magazineCapacity, int bulletCount, double bulletSpeed, double bulletDamage, bool friendly, TextureType texture, TextureType bulletTexture);
    virtual bool shot(double cordX, double cordY, double shotAngle, std::vector<Entity*>& entities) = 0;
    void reloading();

    void startAnimation(Animations animation) override;
    void startAnimation(Animations animation, int);
    void getAnimationState(Animations& animation, int& frame) override;
    void updateAnimation() override;
};