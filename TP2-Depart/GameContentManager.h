#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

using namespace sf;

class GameContentManager
{
public:
	GameContentManager() {}
	bool loadContent();
	const Texture& getBackgroundTexture() const;
	const Texture& getCharacterTexture(int characterNb) const;
	const Texture& getCollectableTexture() const;
	const Texture& getFlagTexture() const;
	const Texture& getEnemyTexture() const;
	const Texture& getHudBackgroundTexture() const;
	const Font& getFont() const;
	const SoundBuffer& getScreamSound() const;
	const SoundBuffer& getWhooshSound() const;

private:
	Texture backgroundTexture;
	Texture hudBackground;
	Texture character1;
	Texture character2;
	Texture collectable;
	Texture flag;
	Texture enemy;
	Font font;
	SoundBuffer scream;
	SoundBuffer whoosh;
};