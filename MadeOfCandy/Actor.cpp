
#include "Actor.h"

Actor::Actor(string filename, int width, int height,int pathX, int pathY, Game* game) {
	this->game = game;

	texture = game->getTexture(filename);

	this->x = pathX*PATH_X;
	this->y = LIMIT_Y+pathY*PATH_Y;

	this->fileWidth = width;
	this->fileHeight = height;

	this->width = width;
	this->height = height;

	this->pathX = pathX;
	this->pathY = pathY;
}

void Actor::draw() {
	SDL_Rect source;
	source.x = 0;
	source.y = 0;
	source.w = fileWidth; 
	source.h = fileHeight;

	SDL_Rect destination;
	destination.x = x - width / 2;
	destination.y = y - height / 2;
	destination.w = width;
	destination.h = height;

	SDL_RenderCopyEx(game->getRenderer(),
		texture, &source, &destination, 0, NULL, SDL_FLIP_NONE);
}

bool Actor::isOverlap(Actor* actor) {
	if (actor->getPathX() == getPathX() && actor->getPathY() == getPathY()) {

		return true;
	}
	return false;
}

bool Actor::isInRender() {
	if (x - width / 2 <= WIDTH && x + width / 2 >= 0 &&
		y - height / 2 <= HEIGHT && y + height / 2 >= 0) {
		return true;
	}
	return false;
}

int Actor::getPathX() {
	return pathX;
}
int Actor::getPathY() {
	return pathY;
}


int Actor::getX() {
	return this->x;
}
int Actor::getY() {
	return this->y;
}
int Actor::getWidth() {
	return this->width;
}
int Actor::getHeight() {
	return this->height;
}
int Actor::getFileWidth() {
	return this->fileWidth;
}
int Actor::getFileHeight() {
	return this->fileHeight;
}
Game* Actor::getGame() {
	return this->game;
}

void Actor::incrementX(float increment) {
	x = x + increment*PATH_X;
	pathX = pathX +increment;
}
void Actor::incrementY(float increment) {
	y = y + increment*PATH_Y;
	pathY = pathY + increment;
}

Actor::~Actor() {
	
}

