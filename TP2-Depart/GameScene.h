#pragma once
#include "Scene.h"
#include "GameContentManager.h"
#include "Inputs.h"
#include "Player.h"
#include "Collectable.h"
#include "Hud.h"
#include "Enemy.h"
#include "Flag.h"

class GameScene : public Scene
{
public:
	GameScene(int characterNb);
	scenes run();
	bool init(RenderWindow* const window, Event* const event);
	String getEndMsg();
	bool getHasWon();

private:
	void getInputs() override;
	void update() override;
	void draw() override;
	bool unload() override;
	void ajustCrossingWorldLimits();
	void manageEnemySpawn();
	void managePlayerAndEnemyCollision();
	void managePlayerAndCollectableCollision();
	void resetGame();

	View view;
	View hudView;

	GameContentManager gameContentManager;
	Inputs inputs;
	Hud hud;
	Music music;

	Sprite background;

	bool endState = false;
	String endMsg = "";
	bool hasWon;

	int score = 0;
	int nbLives = 3;

	int characterNb;
	Player player;
	const float GRAVITY = 0.65;

	const int PLAYER_DYING_TIME = 4 * 60;
	const int PLAYER_CELEBRATING_TIME = 3 * 60;
	int playerEndTimer;

	static const int NB_COLLECTABLES = 9;
	static const int COLLECTABLES_VALUE = 10;
	Collectable collectibles[NB_COLLECTABLES];

	Flag flag;

	static const int NB_ENEMY = 15;
	static const int ENEMY_VALUE = 5;
	Enemy enemy[NB_ENEMY];

	const int X_SAFE_ZONE = 9000;
	const int WIN_ZONE = 9650;
	const int MAX_INITIAL_ENEMY_SPAWN_TIME = 3.5 * 60;
	const int MIN_INITIAL_ENEMY_SPAWN_TIME = 1 * 60;
	int enemySpawnTimer = MAX_INITIAL_ENEMY_SPAWN_TIME;

	const int HELPER_ENEMY_COLLISION = 9;

	const Vector2i PLAYER_STARTING_POINT = { 200, 550 };
};