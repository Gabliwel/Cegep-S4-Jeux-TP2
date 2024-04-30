#include "Enemy.h"
#include "Constants.h"

Enemy::Enemy()
{
}

Enemy::~Enemy()
{
	delete intRectsDead[0];
	for (int i = 0; i < ANIM_RUN; i++)
	{
		delete intRectsRun[i];
	}
}

bool Enemy::init(const Texture& texture, const SoundBuffer& soundBuffer)
{

	animationState = AnimationState::run;
	setTexture(texture);

	intRectsDead[0] = new IntRect();
	intRectsDead[0]->left = 0;
	intRectsDead[0]->top = 0;
	intRectsDead[0]->height = HEIGHT;
	intRectsDead[0]->width = WIDTH;

	for (int i = 0; i < ANIM_RUN; i++)
	{
		intRectsRun[i] = new IntRect();
		intRectsRun[i]->left = WIDTH * i;
		intRectsRun[i]->top = HEIGHT;
		intRectsRun[i]->height = HEIGHT;
		intRectsRun[i]->width = WIDTH;
	}
	deathSound.setBuffer(soundBuffer);
	setTextureRect(*intRectsRun[0]);
	setCollisionRadius(WIDTH);
	setScale(2, 2);
	setOrigin(WIDTH /2, HEIGHT/2);

	return true;
}

void Enemy::die()
{
	deathSound.play();
	dyingAnimationTimer = DYING_ANIMATION_TIME;
	animationState = AnimationState::dead;
	setTextureRect(*intRectsDead[0]);
	animator = 0;
	frameCounter = 0;
}

void Enemy::update()
{
	if (!isActive()) return;

	if (isDead())
	{
		if (dyingAnimationTimer-- < 0)
		{
			deactivate();
		}
		else
		{
			rotate(1 * 3);
			setPosition(getPosition().x, getPosition().y + 4);
		}
		return;
	}

	if (++frameCounter % ANIMATION_SPEED == 0)
	{
		if (++animator == ANIM_RUN)
			animator = 0;

		setTextureRect(*intRectsRun[animator]);
	}
	move(-MOVE_SPEED, 0);
	if (getPosition().x < 0 - getGlobalBounds().width)
	{
		deactivate();
	}
	
}

bool Enemy::isDead()
{
	return animationState == AnimationState::dead;
}

void Enemy::spawn(Vector2f playerPosition)
{
	animationState = AnimationState::run;
	setPosition(playerPosition.x + WINDOW_WIDTH / 2 + (getGlobalBounds().width*2), Y_LEVEL);
	rotate(360 - getRotation());
	animator = 0;
	frameCounter = 0;
	activate();
}
