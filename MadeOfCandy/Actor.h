
#pragma once

#include "Game.h"

/**
* Class thet represents a visual element in the game
*/
class Actor
{
public:
	/**
	* Constructor of the class, it needs:
	* 
	* filename to get the name of the image
	* x, y position of the elements in the game
	* width, height size of the element in the game
	* game instance of the game
	*/
	Actor(string filename, float x, float y, int width, int height, Game* game);
	virtual void draw();
	int getX();
	int getY();
	float getVx();
	float getVy();
	int getWidth();
	int getHeight();
	int getFileWidth();
	int getFileHeight();
	Game* getGame();

private:
	SDL_Texture* texture;
	int x;
	int y;
	float vx;
	float vy;
	int width;
	int height;
	int fileWidth;
	int fileHeight;
	Game* game; 
};

