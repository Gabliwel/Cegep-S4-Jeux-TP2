#include "Hud.h"
#include "Constants.h"

Hud::Hud()
{
}

void Hud::hudInit(const GameContentManager& gameContentManager)
{
	points.setFont(gameContentManager.getFont());
	points.setPosition(10.0f, 40.0f);

	lives.setFont(gameContentManager.getFont());
	lives.setColor(Color::Black);
	lives.setFillColor(Color::White);
	lives.setPosition(10.0f, 90.0f);

	bigMsg.setFont(gameContentManager.getFont());
	bigMsg.setString("");
	bigMsg.setCharacterSize(50);
	bigMsg.setOrigin(bigMsg.getLocalBounds().width / 2, bigMsg.getLocalBounds().height / 2);
	bigMsg.setPosition(WINDOW_WIDTH / 2, 300.0f);

	background.setTexture(gameContentManager.getHudBackgroundTexture());
	background.setScale(.4, .4);
}


void Hud::setBigMsg(String msg)
{
	bigMsg.setString(msg);
	bigMsg.setOrigin(bigMsg.getLocalBounds().width / 2, bigMsg.getLocalBounds().height / 2);
	bigMsg.setPosition(WINDOW_WIDTH / 2, 300.0f);
}

void Hud::hubUpdate(int currentPoints, int currentLives)
{
	points.setString("Score: " + std::to_string(currentPoints));
	lives.setString("Lives: " + std::to_string(currentLives));
}


void Hud::draw(RenderWindow& renderWindow)
{
	renderWindow.draw(background);
	renderWindow.draw(points);
	renderWindow.draw(lives);
	renderWindow.draw(bigMsg);
}
