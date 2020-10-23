#include "SingletonGame.h"

SingletonGame::SingletonGame() {
}

Game* SingletonGame::getInstance() {
	if (this->game == nullptr) {
		this->game = new Game();
	}
	return this->game;
}
