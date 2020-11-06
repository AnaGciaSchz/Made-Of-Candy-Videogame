
#include "GameLayer.h"

GameLayer::GameLayer(Game* game) : Layer(game) {
	init();
}

void GameLayer::init() {
	angel = new Angel(50, 50, getGame());
}

void GameLayer::processControls() {
}

void GameLayer::update() {
	cout << "update GameLayer" << endl;
}

void GameLayer::draw() {
	angel->draw();
	SDL_RenderPresent(getGame()->getRenderer()); // Renderiza
}

