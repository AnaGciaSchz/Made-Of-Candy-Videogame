#include "Layer.h"

Layer::Layer(Game* game) {
	this->game = game;
}

Game* Layer::getGame() {
	return game;
}