#include "EndSceneContentManager.h"

bool EndSceneContentManager::loadContent()
{
	if (!backgroundTexture.loadFromFile("Assets\\Sprites\\background1.png")) return false;
	if (!flag.loadFromFile("Assets\\Sprites\\collectable2.png")) return false;
	if (!font.loadFromFile("Assets\\Fonts\\RandomFont.otf")) return false;
	return true;
}

const Texture& EndSceneContentManager::getEndScreenTexture() const { return backgroundTexture; }

const Texture& EndSceneContentManager::getFlagTexture() const { return flag; }

const Font& EndSceneContentManager::getFont() const { return font; }
