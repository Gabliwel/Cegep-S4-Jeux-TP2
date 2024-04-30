#include "GameContentManager.h"'

bool GameContentManager::loadContent()
{
	if (!backgroundTexture.loadFromFile("Assets\\Sprites\\background2.png")) return false;
	if (!character1.loadFromFile("Assets\\Sprites\\character1.png")) return false;
	if (!character2.loadFromFile("Assets\\Sprites\\character2.png")) return false;
	if (!collectable.loadFromFile("Assets\\Sprites\\testCollectable.png")) return false;
	if (!flag.loadFromFile("Assets\\Sprites\\collectable2.png")) return false;
	if (!enemy.loadFromFile("Assets\\Sprites\\enemy.png")) return false;
	if (!hudBackground.loadFromFile("Assets\\Sprites\\background3.png")) return false;
	if (!font.loadFromFile("Assets\\Fonts\\RandomFont2.ttf")) return false;
	if (!scream.loadFromFile("Assets\\Sounds\\Scream.ogg")) return false;
	if (!whoosh.loadFromFile("Assets\\Sounds\\Whoosh.ogg")) return false;
	return true;
}

const Texture& GameContentManager::getBackgroundTexture() const { return backgroundTexture; }

const Texture& GameContentManager::getCharacterTexture(int characterNb) const
{
	if (characterNb == 1) return character1;
	else if (characterNb == 2)return character2;
	else throw std::invalid_argument("received invalid characterNb");
}

const Texture& GameContentManager::getCollectableTexture() const { return collectable; }

const Texture& GameContentManager::getFlagTexture() const { return flag; }

const Texture& GameContentManager::getEnemyTexture() const { return enemy; }

const Texture& GameContentManager::getHudBackgroundTexture() const { return hudBackground; }

const Font& GameContentManager::getFont() const { return font; }

const SoundBuffer& GameContentManager::getScreamSound() const
{
	return scream;
}

const SoundBuffer& GameContentManager::getWhooshSound() const
{
	return whoosh;
}

