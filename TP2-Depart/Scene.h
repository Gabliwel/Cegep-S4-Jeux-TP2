#pragma once
#include <SFML/Graphics.hpp>
using namespace sf;

/// <summary>
/// Classe abstraite avec aucune m�thode concr�tis�e.  Un .h suffit donc.
/// </summary>
class Scene
{

public:
	//Quand vos ajouterez des sc�nes, ajouter un enum ici.  Exit et Fail sont des marqueurs de sortie
	enum scenes { TITLE, GAME, END, EXIT, FAIL };

	virtual ~Scene() {}  //Pour que le destructeur de l'objet en m�moire soit apell�
	virtual scenes run() = 0;
	virtual bool init(RenderWindow* const window, Event* const event) = 0;
	//Const avant le pointeur rend l'objet point� constant: on ne peut que le lire, on ne peut le modifier.
	//Const apr�s le type rend le pointeur constant, en ce sens qu'on ne peut changer ce vers quoi il pointe mais l'objet lui-m�me est modifiable


protected:
	//La boucle de jeu est maintenant g�r�e par la sc�ne
	virtual void getInputs() = 0;
	virtual void update() = 0;
	virtual void draw() = 0;
	virtual bool unload() = 0;

	RenderWindow* mainWin;
	Event* event;

	/// <summary>
	/// � la fin de chaque sc�ne, on indique � Game quelle nouvelle sc�ne elle doit charger.
	/// </summary>
	Scene::scenes transitionToScene;
	bool isRunning;
};