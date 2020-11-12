#pragma once

#include "Layer.h"

#include "Background.h"

#include "Angel.h"
#include "TheGirl.h"

#include "Enemy.h"
#include "Blob.h"

#include "Cookie.h"

#include "Text.h"
#include "Audio.h"

#include <fstream> 
#include <sstream> 

/**
* Layer for the execution of the game
*/
class GameLayer : public Layer
{
public:
	/**
	* Constructor of the class
	*/
	GameLayer(Game* game);


	/**
	* Method to iniciate the game
	*/
	void init() override;
	/**
	* Method to process the user's actions
	*/
	void processControls() override;
	/**
	* Method to update the game depending of the urser's actions
	*/
	void update() override;
	/**
	* Method to draw the graphics of the game
	*/
	void draw() override;

	/**
	* Method to control the movement
	*/
	void keysToControls(SDL_Event event);

	/**
	* Method to control colisions with enemies
	*/
	void enemyColisions();


	/**
	* Method to control colisions with cookies
	*/
	void cookieColisions();

	void loadMap(string name);
	void loadMapObject(char character, float x, float y);


private:
	/**
	* The player
	*/
	Angel* angel;

	/**
	* The girl
	*/
	TheGirl* girl;

	/**
	* The background
	*/
	Background* background;

	/**
	* Controls to move and interact
	*/
	bool controlShoot;
	bool controlMoveElement;
	int controlMoveY;
	int controlMoveX;

	/**
	* Enemies of the level
	*/
	list<Enemy*> enemies;

	/**
	* Cookies of the level
	*/
	list<Cookie*> cookies;

	/**
	* Movable items of the level
	*/
	list<Movable*> movables;

	/**
	* Icon and text for the lifes
	*/
	Actor* lifes;
	Text* textLifes;

	/**
	* Number of paths in the game
	*/
	int paths;

	Audio* audioBackground;

	int mapWidth;


};


