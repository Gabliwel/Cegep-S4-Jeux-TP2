#include "Player.h"

Player::Player()
{
}

Player::~Player()
{
	delete intRectsIdle[0];
	delete intRectsDead[0];
	for (int i = 0; i < ANIM_RUN; i++)
	{
		delete intRectsRun[i];
	}
	for (int i = 0; i < ANIM_JUMP; i++)
	{
		delete intRectsJump[i];
	}
	for (int i = 0; i < ANIM_DANCE; i++)
	{
		delete intRectsDance[i];
	}
}

bool Player::init(const Texture& texture, const int leftLimit, const int rightLimit, const SoundBuffer& soundBuffer)
{
	animationState = AnimationState::idle;
	setTexture(texture);

	//RECTANGLES D'ANIMATION POUR LE NIVEAU IDLE
	intRectsIdle[0] = new IntRect();
	intRectsIdle[0]->left = 0;
	intRectsIdle[0]->top = RECTANGLE_HEIGHT * LEVEL_IDLE;
	intRectsIdle[0]->height = RECTANGLE_HEIGHT;
	intRectsIdle[0]->width = RECTANGLE_WIDHT;

	//RECTANGLES D'ANIMATION POUR LE NIVEAU DEAD
	intRectsDead[0] = new IntRect();
	intRectsDead[0]->left = 0;
	intRectsDead[0]->top = RECTANGLE_HEIGHT * LEVEL_DEAD;
	intRectsDead[0]->height = RECTANGLE_HEIGHT;
	intRectsDead[0]->width = RECTANGLE_WIDHT;

	//RECTANGLES D'ANIMATION POUR LE NIVEAU COURSE
	for (int i = 0; i < ANIM_RUN; i++)
	{
		intRectsRun[i] = new IntRect();
		intRectsRun[i]->left = RECTANGLE_WIDHT * i;
		intRectsRun[i]->top = RECTANGLE_HEIGHT * LEVEL_RUN;
		intRectsRun[i]->height = RECTANGLE_HEIGHT;
		intRectsRun[i]->width = RECTANGLE_WIDHT;
	}

	//RECTANGLES D'ANIMATION POUR LE NIVEAU SAUT
	for (int i = 0; i < ANIM_JUMP; i++)
	{
		intRectsJump[i] = new IntRect();
		intRectsJump[i]->left = RECTANGLE_WIDHT * i;
		intRectsJump[i]->top = RECTANGLE_HEIGHT * LEVEL_JUMP + 5;
		intRectsJump[i]->height = RECTANGLE_HEIGHT;
		intRectsJump[i]->width = RECTANGLE_WIDHT;
	}

	//RECTANGLES D'ANIMATION POUR LE NIVEAU DANCE
	for (int i = 0; i < ANIM_DANCE; i++)
	{
		intRectsDance[i] = new IntRect();
		intRectsDance[i]->left = RECTANGLE_WIDHT * i;
		intRectsDance[i]->top = RECTANGLE_HEIGHT * LEVEL_DANCE;
		intRectsDance[i]->height = RECTANGLE_HEIGHT;
		intRectsDance[i]->width = RECTANGLE_WIDHT;
	}

	setTextureRect(*intRectsIdle[0]);
	deathSound.setBuffer(soundBuffer);
	setOrigin(RECTANGLE_WIDHT / 2, RECTANGLE_HEIGHT / 2);

	levelLeftLimit = leftLimit + RECTANGLE_WIDHT / 4;
	levelRightLimit = rightLimit - RECTANGLE_WIDHT / 4;
	setScale(DEFAULT_SCALE, DEFAULT_SCALE);
	setCollisionRadius(12);
	activate();

	return true;
}

void Player::draw(RenderWindow& renderWindow)
{
	if (isActive())
	{
		renderWindow.draw(*this);
	}
}

void Player::setAnimationState(AnimationState animationState)
{
	if (this->animationState != animationState)
	{
		this->animationState = animationState;
		animator = 0;
		frameCounter = 0;
		isIdle = false;
	}
}

void Player::managePlayer(Inputs& inputs, const float floorLevel, const float gravity)
{
	if (!isDead())
	{
		if (!isCelebrating())
		{

			horizontal = inputs.horizontal;
			manageMovement();
			manageJump(inputs.jump, floorLevel, gravity);
		}
		else
		{
			manageJump(false, floorLevel, gravity);
		}
	}
	animate();
}

void Player::manageMovement()
{
	if (horizontal == 0)
	{
		if (!isJumping && animationState != AnimationState::celebrating)
			setAnimationState(AnimationState::idle);

		return;
	}

	isIdle = false;
	int tempMove = SPEED;

	if (horizontal < 0)
	{
		tempMove *= -1;
		setScale(-DEFAULT_SCALE, DEFAULT_SCALE);
	}
	else
	{
		setScale(DEFAULT_SCALE, DEFAULT_SCALE);
	}

	move(tempMove, 0);

	if (getPosition().x < levelLeftLimit + getGlobalBounds().width / 2)
		setPosition(levelLeftLimit + getGlobalBounds().width / 2, getPosition().y);
	else if (getPosition().x > levelRightLimit - getGlobalBounds().width / 2)
		setPosition(levelRightLimit - getGlobalBounds().width / 2, getPosition().y);

	if (!isJumping && animationState != AnimationState::celebrating)
		setAnimationState(AnimationState::walking);

}

void Player::manageJump(bool jumpButtonPressed, float floorLevel, float gravity)
{
	if (!isJumping && !jumpButtonPressed && rightToInputJump) return;


	if (!isJumping && jumpButtonPressed && rightToInputJump)
	{
		isJumping = true;
		setAnimationState(AnimationState::jumping);
		isIdle = false;

		actualJumpForce = INITIAL_JUMP_FORCE;
		actualJumpTime = JUMP_TIME;
	}

	if (isJumping && rightToInputJump)
	{
		actualJumpForce += JUMP_FORCE_BY_FRAME;
		actualJumpTime--;

		if (actualJumpTime == 0 || !jumpButtonPressed)
		{
			actualJumpTime = 0;
			rightToInputJump = false;
		}
	}

	if (isJumping)
	{
		actualJumpForce += gravity;
		move(0, actualJumpForce);

		if (getPosition().y > floorLevel)
		{
			setPosition(getPosition().x, floorLevel);
			actualJumpForce = 0.0f;
			actualJumpTime = 0;
			isJumping = false;
		}
	}

	if (!isJumping && !jumpButtonPressed && !rightToInputJump)
		rightToInputJump = true;
}

void Player::animate()
{
	if (isIdle) return;

	if (animationState == AnimationState::idle)
	{
		isIdle = true;
		setTextureRect(*intRectsIdle[0]);
		return;
	}

	if (++frameCounter % ANIMATION_SPEED == 0)
	{
		if (animationState == AnimationState::walking)
		{
			if (++animator == ANIM_RUN)
				animator = 0;

			setTextureRect(*intRectsRun[animator]);
		}
		else if (animationState == AnimationState::jumping)
		{
			if (++animator == ANIM_JUMP)
				animator = ANIM_JUMP - 1;

			setTextureRect(*intRectsJump[animator]);
		}
		else if (animationState == AnimationState::dead)
		{
			setTextureRect(*intRectsDead[0]);
			rotate(getScale().x * (-1 * 75));
			if (getPosition().y < 350)
			{
				knockback = -DEFAULT_KNOCKBACK;
			}
			setPosition(getPosition().x, getPosition().y - knockback);
		}
		else if (animationState == AnimationState::celebrating)
		{
			if (++animator == ANIM_DANCE)
				animator = 0;

			setTextureRect(*intRectsDance[animator]);
		}
	}
}

void Player::celebrate()
{
	isIdle = false;
	setAnimationState(AnimationState::celebrating);
}

void Player::die()
{
	deathSound.play();
	knockback = DEFAULT_KNOCKBACK;
	isIdle = false;
	isJumping = false;
	animationState = AnimationState::dead;
}

bool Player::isDead()
{
	return animationState == AnimationState::dead;
}

bool Player::isCelebrating()
{
	return animationState == AnimationState::celebrating;
}

void Player::reset()
{
	rotate(360 - getRotation());
	animationState = AnimationState::idle;
}
