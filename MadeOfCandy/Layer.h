#pragma once
#include "Game.h"
class Game; //To find the Game class and dont get errors

/**
* Superclass for the different layers of the game
*/
class Layer
{
public:
	/**
	* Constructor of the class
	*/
	Layer();
	/**
	* Method with the basic operations to initiate the layer
	*/
	virtual void init() {};

	//Methods to process users controls, update elements and draw them
	virtual void processControls() {};
	virtual void update() {};
	virtual void draw() {};
};

