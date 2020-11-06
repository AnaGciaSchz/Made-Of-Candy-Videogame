#pragma once

#include "Layer.h"
#include "Angel.h"
#include "TheGirl.h"
#include "Background.h"


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

	/** To see if the user has touched a key
	*/
	bool keyDown;

	/**
	* Controls to move and interact
	*/
	bool controlShoot = false;
	bool controlMoveElement = false;
	int controlMoveY = 0;
	int controlMoveX = 0;

};


