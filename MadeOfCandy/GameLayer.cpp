
#include "GameLayer.h"

GameLayer::GameLayer(Game* game) : Layer(game) {
	init();
}

void GameLayer::init() {
	angel = new Angel(50, 50, getGame());
	background = new Background("res/world/City.png", WIDTH * 0.5, HEIGHT * 0.5, getGame());

	keyDown == false;;
}

void GameLayer::processControls() {
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		keysToControls(event);
	}
//	angel->shoot(controlShoot);
//	angel->moveElement(controlMoveElement);
	if (controlMoveX > 0 || controlMoveX < 0) {
		angel->moveX(controlMoveX);
		controlMoveX = 0;
	}

	if (controlMoveY > 0 || controlMoveY < 0) {
		angel->moveY(controlMoveY);
		controlMoveY = 0;
	}


}

void GameLayer::update() {
	angel->update();
	cout << "update GameLayer" << endl;
}

void GameLayer::draw() {
	background->draw();

	angel->draw();

	SDL_RenderPresent(getGame()->getRenderer()); 
}

void GameLayer::keysToControls(SDL_Event event) {
	if (event.type == SDL_KEYDOWN) {
		int code = event.key.keysym.sym;

		switch (code) {
		case SDLK_d: 
			controlMoveX = 1;
			break;
		case SDLK_a: 
			controlMoveX = -1;
			break;
		case SDLK_w: 
			controlMoveY = -1;
			break;
		case SDLK_s: 
			controlMoveY = 1;
			break;
		case SDLK_SPACE: 
			controlShoot = true;
			break;
		case SDLK_LSHIFT:
			controlMoveElement = true;
			break;
		}
	}
}


