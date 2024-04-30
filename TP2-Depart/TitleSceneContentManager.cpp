#include "TitleSceneContentManager.h"

bool TitleSceneContentManager::loadContent()
{
	if (!backgroundTexture.loadFromFile("Assets\\Sprites\\background1.png")) return false;
	if (!character1.loadFromFile("Assets\\Sprites\\character1-1.png")) return false;
	if (!character2.loadFromFile("Assets\\Sprites\\character2-1.png")) return false;
	if (!font.loadFromFile("Assets\\Fonts\\RandomFont.otf")) return false;
	return true;
}

const Texture& TitleSceneContentManager::getTitleScreenTexture() const
{
	return backgroundTexture;
}

const Texture& TitleSceneContentManager::getC1Texture() const
{
	return character1;
}

const Texture& TitleSceneContentManager::getC2Texture() const
{
	return character2;
}

const Font& TitleSceneContentManager::getFont() const
{
	return font;
}
