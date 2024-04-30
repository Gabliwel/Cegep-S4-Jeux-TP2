#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Inputs.h"
#include "GameObject.h"

using namespace sf;
	class Player : public GameObject
	{
	public:
		Player();
		~Player();

		const enum DIRECTIONS { LEFT = -1, RIGHT = 1, UP = 2, DOWN = -2 };

		bool init(const Texture& texture, const int leftLimit, const int rightLimit, const SoundBuffer& soundBuffer);
		void draw(RenderWindow& renderWindow);

		void managePlayer(Inputs& inputs, const float floorLevel, const float gravity);

		void celebrate();
		void die();
		bool isDead();
		bool isCelebrating();

		void reset();

	private:
		void manageMovement();
		void manageJump(const bool jumpButtonPressed, const float floorLevel, const float gravity);
		void animate();

		enum AnimationState { idle, walking, jumping, celebrating, dead };
		const int RECTANGLE_WIDHT = 60;
		const int RECTANGLE_HEIGHT = 73;
		const int DEFAULT_SCALE = 3;

		void setAnimationState(AnimationState animationState);

		Sound deathSound;

		Texture texture;

		float levelLeftLimit;
		float levelRightLimit;

		static const int ANIM_IDLE = 1;
		static const int LEVEL_IDLE = 0;
		IntRect* intRectsIdle[ANIM_IDLE];

		static const int ANIM_RUN = 6;
		static const int LEVEL_RUN = 1;
		IntRect* intRectsRun[ANIM_RUN];

		static const int ANIM_JUMP = 4;
		static const int LEVEL_JUMP = 2;
		IntRect* intRectsJump[ANIM_JUMP];

		static const int ANIM_DEAD = 1;
		static const int LEVEL_DEAD = 3;
		IntRect* intRectsDead[ANIM_DEAD];

		static const int ANIM_DANCE = 5;
		static const int LEVEL_DANCE = 4;
		IntRect* intRectsDance[ANIM_DANCE];

		AnimationState animationState;
		int animator = 0;
		int frameCounter = 0;
		const int ANIMATION_SPEED = 12;

		const float SPEED = 7;

		bool isIdle = true;
		bool isJumping = false;
		bool rightToInputJump = true;

		const int JUMP_TIME = 32.0f;
		const float INITIAL_JUMP_FORCE = -17.5f;
		const float JUMP_FORCE_BY_FRAME = -0.3f;

		int horizontal = 0;

		int actualJumpTime = 0.0f;
		float actualJumpForce = 0.0f;

		const int DEFAULT_KNOCKBACK = 25;
		int knockback = DEFAULT_KNOCKBACK;
	};

