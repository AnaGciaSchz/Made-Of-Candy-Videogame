#pragma once

#include "Layer.h"


/**
* Layer for the execution of the game
*/
class GameLayer : public Layer
{
public:
	/**
	* Constructor of the class
	*/
	GameLayer();
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
};


