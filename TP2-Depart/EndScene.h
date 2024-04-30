#pragma once
#include "Scene.h"
#include "EndSceneContentManager.h"
#include "Flag.h"

class EndScene : public Scene
{
public:
	EndScene(String endMessage, bool hasWon);
	scenes run();
	bool init(RenderWindow* const window, Event* const event);

private:
	void getInputs() override;
	void update() override;
	void draw() override;
	bool unload() override;

	void transition(scenes exitScene);

	View view;
	EndSceneContentManager contentManager;

	Flag flag1;
	Flag flag2;

	bool hasWon;

	Sprite img;
	Text msg;

	Music music;
};