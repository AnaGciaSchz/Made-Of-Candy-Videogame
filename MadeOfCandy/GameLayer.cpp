
#include "GameLayer.h"

GameLayer::GameLayer() {
	init();
}

void GameLayer::init() {
}

void GameLayer::processControls() {
}

void GameLayer::update() {
	cout << "update GameLayer" << endl;
}

void GameLayer::draw() {
	Game* game = Game::getInstance();
	SDL_RenderPresent(game->getRenderer()); // Renderiza
}

