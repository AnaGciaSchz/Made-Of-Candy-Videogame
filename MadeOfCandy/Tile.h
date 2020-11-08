
#pragma once

#include "Actor.h"
/**
* Class that represents an interactive element
*/
class Tile : public Actor
{
public:
	Tile(string filename, int width, int height, int pathX, int pathY, Game* game);
};

