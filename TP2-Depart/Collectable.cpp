#include "Collectable.h"

Collectable::Collectable()
{
}

Collectable::~Collectable()
{
	delete intRectsNotTaken[0];
	for (int i = 0; i < ANIM_TAKEN; i++)
	{
		delete intRectsTaken[i];
	}
}

bool Collectable::init(const Texture& texture, const SoundBuffer& soundBuffer)
{
	animationState = AnimationState::notTaken;
	setTexture(texture);

	intRectsNotTaken[0] = new IntRect();
	intRectsNotTaken[0]->left = 0;
	intRectsNotTaken[0]->top = 0;
	intRectsNotTaken[0]->height = HEIGHT_NOT_TAKEN;
	intRectsNotTaken[0]->width = WIDTH_NOT_TAKEN;

	sound.setBuffer(soundBuffer);

	for (int i = 0; i < ANIM_TAKEN; i++)
	{
		intRectsTaken[i] = new IntRect();
		intRectsTaken[i]->left = WIDTH_TAKEN * i;
		intRectsTaken[i]->top = HEIGHT_NOT_TAKEN;
		intRectsTaken[i]->height = HEIGHT_TAKEN;
		intRectsTaken[i]->width = WIDTH_TAKEN;
	}

	setTextureRect(*intRectsNotTaken[0]);
	setOrigin(WIDTH_NOT_TAKEN / 2, HEIGHT_NOT_TAKEN / 2);;
	randomize();
	activate();

	return true;
}

void Collectable::collected()
{
	animationState = AnimationState::taken;
	sound.play();
}

void Collectable::update()
{
	if (!isActive()) return;
	if (animationState == AnimationState::notTaken)
	{
		floating();
		setTextureRect(*intRectsNotTaken[0]);
		return;
	}


	if (++frameCounter % ANIMATION_SPEED == 0)
	{
		if (++animator == ANIM_TAKEN)
		{
			deactivate();
			return;
		}

		setTextureRect(*intRectsTaken[animator]);
	}
}

bool Collectable::isAlreadyCollected()
{
	return animationState == taken;
}

void Collectable::reset()
{
	animator = 0;
	frameCounter = 0;
	setTextureRect(*intRectsNotTaken[0]);
	animationState = AnimationState::notTaken;
	activate();
}

void Collectable::randomize()
{
	floatingOffset = (rand() % 20) - 10;

	floater = (rand() % 2);
	if (floater == 0)
		floater = -1;
}


void Collectable::floating()
{
	floatingOffset += floater;
	move(0, floater);
	if (abs(floatingOffset) == 20)
	{
		floater *= -1;
	}
}

