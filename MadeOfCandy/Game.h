#pragma once
#include <iostream>
#include <string>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <map> 
#include<ctime>

using namespace std;

#include "Layer.h"
class Layer; //To find the Layer class and dont get errors

// General values for the game
#define WIDTH 480
#define HEIGHT 320
/**
* Number of paths in Y
*/
#define PATHS_Y 5
/**
* Number of paths in X
*/
#define PATHS_X 12
/**
* Height of paths
*/
#define PATH_Y 40
/**
* Width of paths
*/
#define PATH_X 40

#define LIMIT_Y 90

#define LEVELS 5

#define INPUTKEYBOARD  1
#define INPUTMOUSE  2

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

	int getCurrentLevel();
	void setCurrentLevel(int level);

	int getInputType();
	void setInputType(int input);

	void setLayer(Layer* layer);
	Layer* getGameLayer();

	void stopGame();
	void changeFont(TTF_Font* font);
	TTF_Font* getFont();

	SDL_Texture* getTexture(string filename);
	map<string, SDL_Texture*> mapTextures; // map - cache



private:
	/**
	* Window of the game
	*/
	SDL_Window* window;

	int currentLevel;

	/**
	* Render of the game
	*/
	SDL_Renderer* renderer;
	/**
	* Layer with the basic logic for the game
	*/
	Layer* gameLayer;

	Layer* layer;
	Layer* menuLayer;
	/**
	* Boolean to execute the game until it need to be quitted
	*/
	bool loopActive; // Activate game

	/**
	* FPS of the game
	*/
	const int FPS = 30;

	/**
	* Font to write
	*/
	TTF_Font* font;

	int input;
};

