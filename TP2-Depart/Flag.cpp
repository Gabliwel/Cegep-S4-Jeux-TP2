#include "Flag.h"

Flag::Flag()
{
}

Flag::~Flag()
{
	delete intRectsNotTaken[0];
	for (int i = 0; i < ANIM_TAKEN; i++)
	{
		delete intRectsTaken[i];
	}
}

bool Flag::init(const Texture& texture)
{
	animationState = AnimationState::notTaken;
	setTexture(texture);

	intRectsNotTaken[0] = new IntRect();
	intRectsNotTaken[0]->left = 0;
	intRectsNotTaken[0]->top = 0;
	intRectsNotTaken[0]->height = HEIGHT_NOT_TAKEN;
	intRectsNotTaken[0]->width = WIDTH_NOT_TAKEN;

	for (int i = 0; i < ANIM_TAKEN; i++)
	{
		intRectsTaken[i] = new IntRect();
		intRectsTaken[i]->left = WIDTH_TAKEN * i;
		intRectsTaken[i]->top = 0;
		intRectsTaken[i]->height = HEIGHT_TAKEN;
		intRectsTaken[i]->width = WIDTH_TAKEN;
	}

	setTextureRect(*intRectsNotTaken[0]);
	setOrigin(WIDTH_NOT_TAKEN / 2, HEIGHT_NOT_TAKEN / 2);
	activate();

	return true;
}

void Flag::touched()
{
	animationState = AnimationState::taken;
}

void Flag::update()
{
	if (!isActive()) return;
	if (animationState == AnimationState::notTaken)
	{
		setTextureRect(*intRectsNotTaken[0]);
		return;
	}


	if (++frameCounter % ANIMATION_SPEED == 0)
	{
		if (++animator == ANIM_TAKEN)
			animator = ANIM_TAKEN -1;

		setTextureRect(*intRectsTaken[animator]);
	}
}
