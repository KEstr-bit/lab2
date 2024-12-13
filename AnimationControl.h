#pragma once
enum Animations
{
	ANIM_SPAWN,
	ANIM_BASE,
	ANIM_MOVE,
	ANIM_ATTACK1,
	ANIM_ATTACK2,
	ANIM_TAKING_DAMAGE,
	ANIM_DIE
};

class AnimationControl
{
public:
	static const float FRAME_SPEED;
	virtual void startAnimation(Animations animation) = 0;
	virtual void getAnimationState(Animations& animation, int& frame) = 0;
	virtual void updateAnimation() = 0;

};
