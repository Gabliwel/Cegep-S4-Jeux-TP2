#pragma once
#include "GameObject.h"

using namespace sf;
class Collectable : public GameObject
{
public:
	Collectable();
	~Collectable();
	bool init(const Texture& texture, const SoundBuffer& soundBuffer);
	void collected();
	void update();
	bool isAlreadyCollected();
	void reset();

private:
	void randomize();
	void floating();

	Sound sound;
	enum AnimationState { notTaken, taken };
	AnimationState animationState;

	static const int ANIM_NOT_TAKEN = 1;
	static const int HEIGHT_NOT_TAKEN = 52;
	static const int WIDTH_NOT_TAKEN = 39;
	IntRect* intRectsNotTaken[ANIM_NOT_TAKEN];

	static const int ANIM_TAKEN = 3;
	static const int HEIGHT_TAKEN = 158;
	static const int WIDTH_TAKEN = 158;
	IntRect* intRectsTaken[ANIM_TAKEN];

	int animator = 0;
	int frameCounter = 0;
	const int ANIMATION_SPEED = 15;

	int floatingOffset;
	int floater;
};
