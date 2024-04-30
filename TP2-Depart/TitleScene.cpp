#include "TitleScene.h"
#include "Constants.h"

TitleScene::TitleScene()
{
	view = View(FloatRect(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT));
}

Scene::scenes TitleScene::run()
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

bool TitleScene::init(RenderWindow* const window, Event* const event)
{
	this->mainWin = window;
	this->event = event;
	isRunning = true;

	if (!titleContentManager.loadContent())
		return false;

	if (!music.openFromFile("Assets\\Music\\Theme.ogg")) return false;
	music.setLoop(true);
	music.play();

	menuImage.setTexture(titleContentManager.getTitleScreenTexture());
	menuImage.setOrigin(menuImage.getTexture()->getSize().x / 2, menuImage.getTexture()->getSize().y / 2);
	menuImage.setPosition(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 3);
	menuImage.setScale(2.2, 2.2);

	character1.setTexture(titleContentManager.getC1Texture());
	character1.setScale(2, 2);
	character1.setOrigin(character1.getTexture()->getSize().x / 2, character1.getTexture()->getSize().y / 2);
	character1.setPosition(WINDOW_WIDTH / 3 + 100, WINDOW_HEIGHT / 2);

	character2.setTexture(titleContentManager.getC2Texture());
	character2.setScale(-2, 2);
	character2.setOrigin(character2.getTexture()->getSize().x / 2, character2.getTexture()->getSize().y / 2);
	character2.setPosition(((WINDOW_WIDTH / 3) * 2) - 100, WINDOW_HEIGHT / 2);
	
	instructions.setString("Appuyez sur 1 pour sélectionner Bob\nAppuyez sur 2 pour sélectionner Roger\n");
	instructions.setFont(titleContentManager.getFont());
	instructions.setCharacterSize(35);
	instructions.setColor(Color::White);
	instructions.setPosition(40, 600);

	return true;
}

int TitleScene::getCharacterNb() const
{
	return characterNb;
}

void TitleScene::getInputs()
{
	//On passe l'événement en référence et celui-ci est chargé du dernier événement reçu!
	while (mainWin->pollEvent(*event))
	{
		//x sur la fenêtre
		if (event->type == Event::Closed)
		{
			transition(scenes::EXIT);
		}
		if (event->type == Event::KeyPressed)
		{
			if (event->key.code == Keyboard::Num1)
			{
				characterNb = 1;
				transition(scenes::GAME);
			}
			else if (event->key.code == Keyboard::Num2)
			{
				characterNb = 2;
				transition(scenes::GAME);
			}
		}
	}
}

void TitleScene::update()
{
	//rien a update ici
}

void TitleScene::draw()
{
	mainWin->clear();
	mainWin->setView(view);

	mainWin->draw(menuImage);
	mainWin->draw(character1);
	mainWin->draw(character2);
	mainWin->draw(instructions);

	mainWin->setView(view);
	mainWin->display();;

}

bool TitleScene::unload()
{
	return true;
}

void TitleScene::transition(scenes exitScene)
{
	isRunning = false;
	transitionToScene = exitScene;
}
