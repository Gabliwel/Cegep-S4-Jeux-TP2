#pragma once
#include <SFML/Graphics.hpp>
using namespace sf;

/// <summary>
/// Classe abstraite avec aucune méthode concrétisée.  Un .h suffit donc.
/// </summary>
class Scene
{

public:
	//Quand vos ajouterez des scènes, ajouter un enum ici.  Exit et Fail sont des marqueurs de sortie
	enum scenes { TITLE, GAME, END, EXIT, FAIL };

	virtual ~Scene() {}  //Pour que le destructeur de l'objet en mémoire soit apellé
	virtual scenes run() = 0;
	virtual bool init(RenderWindow* const window, Event* const event) = 0;
	//Const avant le pointeur rend l'objet pointé constant: on ne peut que le lire, on ne peut le modifier.
	//Const après le type rend le pointeur constant, en ce sens qu'on ne peut changer ce vers quoi il pointe mais l'objet lui-même est modifiable


protected:
	//La boucle de jeu est maintenant gérée par la scène
	virtual void getInputs() = 0;
	virtual void update() = 0;
	virtual void draw() = 0;
	virtual bool unload() = 0;

	RenderWindow* mainWin;
	Event* event;

	/// <summary>
	/// À la fin de chaque scène, on indique à Game quelle nouvelle scène elle doit charger.
	/// </summary>
	Scene::scenes transitionToScene;
	bool isRunning;
};