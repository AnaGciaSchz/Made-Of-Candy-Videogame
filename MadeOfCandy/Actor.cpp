
#include "Actor.h"

Actor::Actor(string filename, float x, float y, int width, int height, Game* game) {
	this->game = game;

	SDL_Surface* surface = IMG_Load(filename.c_str());
	texture = SDL_CreateTextureFromSurface(game->getRenderer(), surface);

	this->x = x;
	this->y = y;

	this->fileWidth = width;
	this->fileHeight = height;

	this->width = width;
	this->height = height;
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
	if (actor->x - actor->width / 2 <= x + width / 2
		&& actor->x + actor->width / 2 >= x - width / 2
		&& actor->y + actor->height / 2 >= y - height / 2
		&& actor->y - actor->height / 2 <= y + height / 2) {

		return true;
	}
	return false;
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
	x = x + increment;
}
void Actor::incrementY(float increment) {
	y = y + increment;
}
