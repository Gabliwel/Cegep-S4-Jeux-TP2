#include "GameScene.h"
#include "Constants.h"

GameScene::GameScene(int characterNb)
{
	this->characterNb = characterNb;
	view = View(FloatRect(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT));
	hudView = View(FloatRect(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT));
}

Scene::scenes GameScene::run()
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

bool GameScene::init(RenderWindow* const window, Event* const event)
{
	this->mainWin = window;
	this->event = event;
	isRunning = true;

	if (!gameContentManager.loadContent())
		return false;

	if (!music.openFromFile("Assets\\Music\\Theme.ogg")) return false;
	music.setLoop(true);
	music.play();

	background.setTexture(gameContentManager.getBackgroundTexture());

	player.init(gameContentManager.getCharacterTexture(characterNb), 0, WORLD_WIDTH, gameContentManager.getScreamSound());
	player.setPosition(PLAYER_STARTING_POINT.x, PLAYER_STARTING_POINT.y);

	flag.init(gameContentManager.getFlagTexture());
	flag.setPosition(9750, 200);

	for (int x = 0; x < NB_COLLECTABLES; x++)
	{
		collectibles[x].init(gameContentManager.getCollectableTexture(), gameContentManager.getScreamSound());
		collectibles[x].setPosition((x + 1) * 900, 150);
	}

	for (int x = 0; x < NB_ENEMY; x++)
	{
		enemy[x].init(gameContentManager.getEnemyTexture(), gameContentManager.getWhooshSound());
	}

	hud.hudInit(gameContentManager);

	return true;
}

String GameScene::getEndMsg()
{
	return endMsg;
}

bool GameScene::getHasWon()
{
	return hasWon;
}

void GameScene::getInputs()
{
	inputs.reset();
	while (mainWin->pollEvent(*event))
	{
		//x sur la fenêtre
		if (event->type == Event::Closed)
		{
			isRunning = false;
			transitionToScene = Scene::scenes::EXIT;
		}
		if (event->type == Event::KeyPressed)
		{
			if (event->key.code == Keyboard::Escape)
			{
				isRunning = false;
				//transitionToScene = Scene::scenes::TITLE;
			}

			if (endState && event->key.code == Keyboard::Enter)
			{
				isRunning = false;
				transitionToScene = Scene::scenes::END;
			}
		}
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))	inputs.horizontal = player.LEFT;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) inputs.horizontal = player.RIGHT;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) inputs.jump = true;
	if (Keyboard::isKeyPressed(Keyboard::P))
	{
		if (!inputs.isInPauseBuffer)
		{
			inputs.isInPauseBuffer = true;
			inputs.isInPause = !inputs.isInPause;
		}
	}
	else
	{
		inputs.isInPauseBuffer = false;
	}
}

void GameScene::update()
{
	if (inputs.isInPause)
	{
		music.pause();
		hud.setBigMsg("PAUSE");
		return;
	}
	if (Music::Paused == music.getStatus())
	{
		music.play();
	}
	hud.setBigMsg("");

	for (int x = 0; x < NB_COLLECTABLES; x++)
	{
		collectibles[x].update();
	}

	for (int x = 0; x < NB_ENEMY; x++)
	{
		enemy[x].update();
	}

	player.managePlayer(inputs, PLAYER_STARTING_POINT.y, GRAVITY);

	flag.update();

	if (player.isDead() && playerEndTimer-- < 0)
	{
		if (nbLives <= 0)
		{
			player.deactivate();
			hud.setBigMsg("GAME OVER\n(APPUYER SUR ENTER)");
			endMsg = "GAME OVER";
			hasWon = false;
			endState = true;
			return;
		}
		else
		{
			resetGame();
		}
	}
	else if (player.isCelebrating() && playerEndTimer-- < 0)
	{
		hud.setBigMsg("VICTORY\n(APPUYER SUR ENTER)");
		endMsg = "VICTORY (SCORE: " + std::to_string(score) + ")";
		hasWon = true;
		endState = true;
		return;
	}

	if (!player.isDead() && !player.isCelebrating())
	{
		managePlayerAndCollectableCollision();
		managePlayerAndEnemyCollision();
		manageEnemySpawn();
		if (player.getGlobalBounds().intersects(flag.getGlobalBounds()))
		{
			flag.touched();
			playerEndTimer = PLAYER_CELEBRATING_TIME;
			player.celebrate();
		}
	}

	hud.hubUpdate(score, nbLives);

	view.setCenter(player.getPosition().x, WORLD_HEIGHT / 2);
	ajustCrossingWorldLimits();
}

void GameScene::draw()
{
	mainWin->clear();
	mainWin->setView(view);

	mainWin->draw(background);

	for (int x = 0; x < NB_COLLECTABLES; x++)
	{
		if(collectibles[x].isActive()) mainWin->draw(collectibles[x]);
	}

	player.draw(*mainWin);

	for (int x = 0; x < NB_ENEMY; x++)
	{
		if (enemy[x].isActive()) mainWin->draw(enemy[x]);
	}

	mainWin->draw(flag);

	mainWin->setView(hudView);
	hud.draw(*mainWin);
	mainWin->setView(view);
	mainWin->display();;
}

bool GameScene::unload()
{
	return true;
}

void GameScene::ajustCrossingWorldLimits()
{
	if (view.getCenter().x < WINDOW_WIDTH /2)
	{
		view.setCenter(WINDOW_WIDTH / 2, view.getCenter().y);
	}
	else if (view.getCenter().x > WORLD_WIDTH - WINDOW_WIDTH / 2)
	{
		view.setCenter(WORLD_WIDTH - WINDOW_WIDTH / 2, view.getCenter().y);
	}

	if (view.getCenter().y < WINDOW_HEIGHT / 2)
	{
		view.setCenter(view.getCenter().x, WINDOW_HEIGHT / 2);
	}
	else if (view.getCenter().y > WORLD_HEIGHT - WINDOW_HEIGHT / 2)
	{
		view.setCenter(view.getCenter().x, WORLD_HEIGHT - WINDOW_HEIGHT / 2);
	}
}

void GameScene::manageEnemySpawn()
{
	if (enemySpawnTimer-- < 0 && player.getPosition().x < X_SAFE_ZONE)
	{
		enemySpawnTimer = rand() % (MAX_INITIAL_ENEMY_SPAWN_TIME - MIN_INITIAL_ENEMY_SPAWN_TIME + 1) + MIN_INITIAL_ENEMY_SPAWN_TIME;
		for (int x = 0; x < NB_ENEMY; x++)
		{
			if (!enemy[x].isActive())
			{
				enemy[x].spawn(player.getPosition());
				return;
			}
		}
	}
}

void GameScene::managePlayerAndEnemyCollision()
{
	for (int x = 0; x < NB_ENEMY; x++)
	{
		if (!enemy[x].isDead() && enemy[x].isActive())
		{
			if (enemy[x].getCollisionCircle().checkCollision(player.getCollisionCircle()))
			{
				//-helper pour la justesse
				if (player.getPosition().y + (player.getGlobalBounds().height / 2) - HELPER_ENEMY_COLLISION < enemy[x].getPosition().y)
				{
					score += ENEMY_VALUE;
					enemy[x].die();
				}
				else
				{
					nbLives--;
					score = 0;
					player.die();
					playerEndTimer = PLAYER_DYING_TIME;
				}
			}
		}
	}
}

void GameScene::managePlayerAndCollectableCollision()
{
	for (int x = 0; x < NB_COLLECTABLES; x++)
	{
		if (!collectibles[x].isAlreadyCollected() && collectibles[x].getGlobalBounds().intersects(player.getGlobalBounds()))
		{
			score += COLLECTABLES_VALUE;
			collectibles[x].collected();
		}
	}
}

void GameScene::resetGame()
{
	music.stop();
	music.play();
	player.reset();
	player.setPosition(PLAYER_STARTING_POINT.x, PLAYER_STARTING_POINT.y);

	for (int x = 0; x < NB_COLLECTABLES; x++)
	{
		collectibles[x].reset();
		collectibles[x].setPosition((x + 1) * 900, 150);
	}

	for (int x = 0; x < NB_ENEMY; x++)
	{
		enemy[x].deactivate();
	}
	enemySpawnTimer = MAX_INITIAL_ENEMY_SPAWN_TIME;
}
