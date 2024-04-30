#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio/Music.hpp>

using namespace sf;

class EndSceneContentManager
{
public:
	EndSceneContentManager() {}
	bool loadContent();
	const Texture& getEndScreenTexture() const;
	const Texture& getFlagTexture() const;
	const Font& getFont() const;

private:
	Texture backgroundTexture;
	Texture flag;
	Font font;
};