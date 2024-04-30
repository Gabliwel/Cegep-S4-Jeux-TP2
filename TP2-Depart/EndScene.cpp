#include "EndScene.h"
#include "Constants.h"

EndScene::EndScene(String endMessage, bool hasWon)
{
	view = View(FloatRect(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT));
	msg.setString(endMessage);
	this->hasWon = hasWon;
}

Scene::scenes EndScene::run()
{
	while (isRunning)
	{
		getInputs();
		update();
		draw();
	}

	if (!unload()) return scenes::FAIL;
	music.stop();
	return transitionToScene;
}

bool EndScene::init(RenderWindow* const window, Event* const event)
{
	this->mainWin = window;
	this->event = event;
	isRunning = true;

	if (!contentManager.loadContent())
		return false;
	if (hasWon)
	{
		if (!music.openFromFile("Assets\\Music\\Won.ogg")) return false;
	} 
	else 
	{
		if (!music.openFromFile("Assets\\Music\\GameOver.ogg")) return false;
	}
	music.setLoop(true);
	music.play();

	flag1.init(contentManager.getFlagTexture());
	flag2.init(contentManager.getFlagTexture());
	flag1.setPosition(WINDOW_WIDTH/3, 200);
	flag2.setPosition((WINDOW_WIDTH / 3)*2, 200);

	if (hasWon)
	{
		flag1.touched();
		flag2.touched();
	}

	img.setTexture(contentManager.getEndScreenTexture());
	img.setOrigin(img.getTexture()->getSize().x / 2, img.getTexture()->getSize().y / 2);
	img.setPosition(1280 / 2, 720 / 3);
	img.setScale(2.2, 2.2);

	msg.setString(msg.getString() + "\nAppuyez sur ENTER pour retourner au menu\n");
	msg.setFont(contentManager.getFont());
	msg.setCharacterSize(35);
	msg.setColor(Color::White);
	msg.setPosition(40, 600);

	return true;
}

void EndScene::getInputs()
{
	while (mainWin->pollEvent(*event))
	{
		//x sur la fenêtre
		if (event->type == Event::Closed)
		{
			transition(scenes::EXIT);
		}
		if (event->type == Event::KeyPressed)
		{
			if (event->key.code == Keyboard::Enter)
			{
				transition(scenes::TITLE);
			}
		}
	}
}

void EndScene::update()
{
	flag1.update();
	flag2.update();
}

void EndScene::draw()
{
	mainWin->clear();
	mainWin->setView(view);

	mainWin->draw(img);
	mainWin->draw(flag1);
	mainWin->draw(flag2);
	mainWin->draw(msg);

	mainWin->setView(view);
	mainWin->display();;
}

bool EndScene::unload()
{
	return true;
}

void EndScene::transition(scenes exitScene)
{
	isRunning = false;
	transitionToScene = exitScene;
}
