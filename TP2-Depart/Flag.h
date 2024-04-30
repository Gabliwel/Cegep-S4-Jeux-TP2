#pragma once

#include "GameObject.h"

using namespace sf;
class Flag : public GameObject
{
public:
	Flag();
	~Flag();
	bool init(const Texture& texture);
	void touched();
	void update();

private:
	enum AnimationState { notTaken, taken };
	AnimationState animationState;

	static const int ANIM_NOT_TAKEN = 1;
	static const int HEIGHT_NOT_TAKEN = 60;
	static const int WIDTH_NOT_TAKEN = 80;
	IntRect* intRectsNotTaken[ANIM_NOT_TAKEN];

	static const int ANIM_TAKEN = 9;
	static const int HEIGHT_TAKEN = 150;
	static const int WIDTH_TAKEN = WIDTH_NOT_TAKEN;
	IntRect* intRectsTaken[ANIM_TAKEN];

	int animator = 0;
	int frameCounter = 0;
	const int ANIMATION_SPEED = 12;
};