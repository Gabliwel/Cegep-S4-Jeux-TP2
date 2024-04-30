#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

class TitleSceneContentManager
{
public:
	TitleSceneContentManager() {}
	bool loadContent();
	const Texture& getTitleScreenTexture() const;
	const Texture& getC1Texture() const;
	const Texture& getC2Texture() const;
	const Font& getFont() const;

private:
	Texture backgroundTexture;
	Font font;
	Texture character1;
	Texture character2;
};