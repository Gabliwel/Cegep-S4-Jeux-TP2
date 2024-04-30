#include "Game.h"
#include "TitleScene.h"
#include "GameScene.h"
#include "EndScene.h"


Game::Game()
{
	//On place dans le contructeur ce qui permet à la game elle-même de fonctionner

	renderWindow.create(VideoMode(WIDTH, HEIGHT, 32), "JSP");  // , Style::Titlebar); / , Style::FullScreen);
	view = renderWindow.getDefaultView();

	//Synchonisation coordonnée à l'écran!  Normalement 60 frames par secondes. À faire absolument
	renderWindow.setVerticalSyncEnabled(true);
	//renderWindow.setFramerateLimit(60);  //Équivalent... normalement, mais pas toujours. À utiliser si la synchonisation de l'écran fonctionne mal.
	//https://www.sfml-dev.org/tutorials/2.5/window-window.php
}

int Game::run()
{
	//Un enum et un pointeur de scene pour faire la manipulation de scène
	Scene::scenes sceneSelector = Scene::scenes::TITLE;
	Scene* activeScene = nullptr; //Pointeur de la super-classe, peut pointer sur n'importe quelle scène

	//Les variables de passage d'information entre scènes devraient être déclarés ici
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
			//Vous allez ajouter d'autre scènes, alors elles devront
			//être ajoutées ici
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

			//La référence de fenêtre est absolument obligatoire.
			//l'event est optionnel (pourrait être tenu par la scène) mais recommandé.
			if (activeScene->init(&renderWindow, &event))
			{
				//Run est la boucle de jeu de la scène
				//À la fin de cette méthode, elle retourne la scène
				//Laquelle on transition
				sceneSelector = activeScene->run();

				//À la fin d'une scène, s'il y a des sauvegardes à faire
				//C'est possible de les faire là.
				TitleScene* tempScene = dynamic_cast<TitleScene*>(activeScene);
				if (tempScene != nullptr)//Donc si le cast a réussi.
				{
					characterNb = tempScene->getCharacterNb();
				}
				else
				{
					GameScene* tempScene2 = dynamic_cast<GameScene*>(activeScene);
					if (tempScene2 != nullptr)//Donc si le cast a réussi.
					{
						endMsg = tempScene2->getEndMsg();
						hasWon = tempScene2->getHasWon();
					}
				}
			}
			else //Si l'initialisation rate, on fail et on nettoie ce qui est à nettoyer
			{
				sceneSelector = Scene::scenes::FAIL;
				//clean-up éventuel faire pour s'assurer  de ne pas avoir de leak
				//(malgré l'échec)				
			}
		}

		//Nécessaire tout ce qui est crée avec new doit être effacé.
		delete activeScene;
		activeScene = nullptr;
	}
}