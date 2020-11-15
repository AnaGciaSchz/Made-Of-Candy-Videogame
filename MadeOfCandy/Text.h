
#pragma once

#include "Game.h"
/**
* Class to write texts
*/
class Text
{
public:
	Text(string content, float x, float y, Game* game);
	void draw();
	string content; // text
	int x;
	int y;
	int width;
	int height;
	Game* game; 

};


