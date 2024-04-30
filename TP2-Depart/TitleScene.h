#pragma once
#include "Scene.h"
#include "TitleSceneContentManager.h"
#include <SFML/Audio/Music.hpp>

class TitleScene : public Scene
{
public:
	TitleScene();
	scenes run();
	bool init(RenderWindow* const window, Event* const event);
	int getCharacterNb() const;

private:
	void getInputs() override;
	void update() override;
	void draw() override;
	bool unload() override;

	void transition(scenes exitScene);

	Music music;
	View view;
	TitleSceneContentManager titleContentManager;

	Sprite character1;
	Sprite character2;
	Sprite menuImage;
	Text instructions;
	int characterNb = 0;
};