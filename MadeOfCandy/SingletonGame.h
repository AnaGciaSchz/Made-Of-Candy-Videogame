#pragma once

#include "Game.h"
/**
* Class to call to only have one Game object created at the time. We will only use
* one instance of Game thanks to this class.
*/
class SingletonGame
{
public:
	/**
	* Constructor of the class
	*/
	SingletonGame();
	/**
	* Method to get the instance of the game
	*/
	Game* getInstance();

private:
	/**
	* Game that the class will be returning
	*/
	Game* game = nullptr;
};

