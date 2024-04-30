#pragma once
#include <SFML/Graphics.hpp>
#include "GameContentManager.h"

using namespace sf;

class Hud
{
public:
	Hud();
	void hudInit(const GameContentManager& gameContentManager);
	void hubUpdate(int currentPoints, int currentLives);
	void draw(RenderWindow& renderWindow);
	void setBigMsg(String msg);
private:
	Text points;
	Text lives;
	Text bigMsg;
	Sprite background;
};

