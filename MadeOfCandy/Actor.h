
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
	Actor(string filename, int width, int height, int pathX, int pathY, Game* game);
	Actor(string filename, int x, int y,int width, int height, int pathX, int pathY, Game* game);
	~Actor(); //destructor
	virtual void draw();
	/**
	* Method to see if the actor that is passed as parameter is overlaping with the actual
	* actor
	*/
	bool isOverlap(Actor* actor);
	/**
	* We need to know if the actor is in the screen
	*/
	bool isInRender();

	int getX();
	int getY();
	int getWidth();
	int getHeight();
	int getFileWidth();
	int getFileHeight();

	Game* getGame();

	void incrementX(float increment);
	void incrementY(float increment);

	int getPathX();
	int getPathY();

protected:
	float x;
	int y;
	/**In which paths is the actor?
	*/
	int pathX;
	int pathY;

private:
	SDL_Texture* texture;
	int width;
	int height;
	int fileWidth;
	int fileHeight;
	Game* game;

};

