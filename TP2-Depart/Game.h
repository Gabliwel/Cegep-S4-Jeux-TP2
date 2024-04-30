#pragma once
#include <SFML/Graphics.hpp>
using namespace sf;

class Game
{
public:
	Game();
	int run();

private:
	const int WIDTH = 1280;
	const int HEIGHT = 720;

	//info de title a game
	int characterNb;

	//info de game a end
	String endMsg;
	bool hasWon;

	RenderWindow renderWindow;
	View view;
	Event event;
};