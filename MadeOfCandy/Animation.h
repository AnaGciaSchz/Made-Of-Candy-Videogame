
#pragma once

#pragma once

#include "Game.h"

/**
* Class to show animations
*/
class Animation
{
public:
	Animation(string filename, float actorWidth, float actorHeight,
		float fileWidth, float fileHeight,
		int updateFrecuence, int totalFrames, Game* game);
	bool update();
	void draw(float x, float y);
	int actorWidth; // Actor Width
	int actorHeight; // Actor height
	int fileWidth; // Sprite Sheet width
	int fileHeight; // Sprite Sheet height
	int currentFrame;
	int totalFrames;
	Game* game;

	SDL_Texture* texture; 
	SDL_Rect source; 
	float frameWidth; 
	float frameHeigt; 
	int updateFrecuence = 0;
	int updateTime = 0;
};

