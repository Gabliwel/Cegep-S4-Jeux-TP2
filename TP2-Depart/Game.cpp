#include "Game.h"
#include "TitleScene.h"
#include "GameScene.h"
#include "EndScene.h"


Game::Game()
{
	//On place dans le contructeur ce qui permet � la game elle-m�me de fonctionner

	renderWindow.create(VideoMode(WIDTH, HEIGHT, 32), "JSP");  // , Style::Titlebar); / , Style::FullScreen);
	view = renderWindow.getDefaultView();

	//Synchonisation coordonn�e � l'�cran!  Normalement 60 frames par secondes. � faire absolument
	renderWindow.setVerticalSyncEnabled(true);
	//renderWindow.setFramerateLimit(60);  //�quivalent... normalement, mais pas toujours. � utiliser si la synchonisation de l'�cran fonctionne mal.
	//https://www.sfml-dev.org/tutorials/2.5/window-window.php
}

int Game::run()
{
	//Un enum et un pointeur de scene pour faire la manipulation de sc�ne
	Scene::scenes sceneSelector = Scene::scenes::TITLE;
	Scene* activeScene = nullptr; //Pointeur de la super-classe, peut pointer sur n'importe quelle sc�ne

	//Les variables de passage d'information entre sc�nes devraient �tre d�clar�s ici
	//int ScoreBuffer = 0;

	while (true)
	{
		//Seules conditions de sortie de toute l'app, une pour les sorties normales, une pour les erreurs
		//On est au seul point de sortie
		if (sceneSelector == Scene::scenes::EXIT)
		{
			return EXIT_SUCCESS;
		}
		else
		{
			//Vous allez ajouter d'autre sc�nes, alors elles devront
			//�tre ajout�es ici
			switch (sceneSelector)
			{
			case Scene::scenes::TITLE:
				activeScene = new TitleScene();
				break;

			case Scene::scenes::GAME:
				activeScene = new GameScene(characterNb);
				break;

			case Scene::scenes::END:
				activeScene = new EndScene(endMsg, hasWon);
				break;
			}

			//La r�f�rence de fen�tre est absolument obligatoire.
			//l'event est optionnel (pourrait �tre tenu par la sc�ne) mais recommand�.
			if (activeScene->init(&renderWindow, &event))
			{
				//Run est la boucle de jeu de la sc�ne
				//� la fin de cette m�thode, elle retourne la sc�ne
				//Laquelle on transition
				sceneSelector = activeScene->run();

				//� la fin d'une sc�ne, s'il y a des sauvegardes � faire
				//C'est possible de les faire l�.
				TitleScene* tempScene = dynamic_cast<TitleScene*>(activeScene);
				if (tempScene != nullptr)//Donc si le cast a r�ussi.
				{
					characterNb = tempScene->getCharacterNb();
				}
				else
				{
					GameScene* tempScene2 = dynamic_cast<GameScene*>(activeScene);
					if (tempScene2 != nullptr)//Donc si le cast a r�ussi.
					{
						endMsg = tempScene2->getEndMsg();
						hasWon = tempScene2->getHasWon();
					}
				}
			}
			else //Si l'initialisation rate, on fail et on nettoie ce qui est � nettoyer
			{
				sceneSelector = Scene::scenes::FAIL;
				//clean-up �ventuel faire pour s'assurer  de ne pas avoir de leak
				//(malgr� l'�chec)				
			}
		}

		//N�cessaire tout ce qui est cr�e avec new doit �tre effac�.
		delete activeScene;
		activeScene = nullptr;
	}
}