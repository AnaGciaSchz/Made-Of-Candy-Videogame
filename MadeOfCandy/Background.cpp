
#include "Background.h"

Background::Background(string filename, float x, float y, Game* game)
	: Actor(filename, WIDTH, HEIGHT,0,0, game) {
	this->x = x;
	this->y = y;

}

