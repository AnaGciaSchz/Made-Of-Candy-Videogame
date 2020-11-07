#pragma once
#include <iostream>
#include <string>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

using namespace std;

#include "Layer.h"
class Layer; //To find the Layer class and dont get errors

// General values for the game
#define WIDTH 480
#define HEIGHT 320

/**
*Class that represents the basic logic in the game (window, render and loop that initiates
* the game)
*/
class Game
{
public:
	/**
	* Loop that initiates the game and only stops if something bad happened or ir the
	* user wants to quit the game
	*/
	void loop();

	/**
	 * Method to render the game
	 */
	SDL_Renderer* getRenderer();

	/**
	* Constructor of the class
	*/
	Game();

	void stopGame();

private:
	/**
	* Window of the game
	*/
	SDL_Window* window;
	/**
	* Render of the game
	*/
	SDL_Renderer* renderer;
	/**
	* Layer with the basic logic for the game
	*/
	Layer* gameLayer;
	/**
	* Boolean to execute the game until it need to be quitted
	*/
	bool loopActive; // Activate game

	/**
	* FPS of the game
	*/
	const int FPS = 30;
};

