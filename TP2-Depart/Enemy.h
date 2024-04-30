#pragma once
#include "GameObject.h"

using namespace sf;
class Enemy : public GameObject
{
public:
	Enemy();
	~Enemy();
	bool init(const Texture& texture, const SoundBuffer& soundBuffer);
	void die();
	void update();
	bool isDead();
	void spawn(Vector2f playerPosition);

private:

	enum AnimationState { run, dead };
	AnimationState animationState;
	Sound deathSound;

	const int MOVE_SPEED = 5;
	const int Y_LEVEL = 565;

	static const int HEIGHT = 95;
	static const int WIDTH = 150;

	static const int ANIM_RUN = 4;
	IntRect* intRectsRun[ANIM_RUN];

	static const int ANIM_DEAD = 1;
	IntRect* intRectsDead[ANIM_DEAD];

	int animator = 0;
	int frameCounter = 0;
	const int ANIMATION_SPEED = 12;

	const int DYING_ANIMATION_TIME = 1 * 60;
	int dyingAnimationTimer = DYING_ANIMATION_TIME;
};