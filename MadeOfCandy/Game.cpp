
#include "Game.h"
#include "GameLayer.h"

SDL_Renderer* Game::getRenderer() {
	return renderer;
}


Game::Game() {
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
		cout << "Error SDL_Init" << SDL_GetError() << endl;
	}
	if (SDL_CreateWindowAndRenderer(WIDTH, HEIGHT, 0, &window, &renderer) < 0) {
		cout << "Error Window y Renderer" << SDL_GetError() << endl;
	}
	SDL_SetWindowTitle(window, "Made of Candy");

	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");

	gameLayer = new GameLayer(this);

	TTF_Init();
	changeFont(TTF_OpenFont("res/fonts/monogram.ttf", 24));


	loopActive = true;
	loop();
}

void Game::loop() {
	//for the fps
	int initTick;
	int endTick;
	int differenceTick;
	while (loopActive) {
		initTick = SDL_GetTicks();

		// get the controls 
		gameLayer->processControls();
		// update elements
		gameLayer->update();
		// draw
		gameLayer->draw();

		endTick = SDL_GetTicks();
		differenceTick = endTick - initTick;

		// To respect trhe fps
		if (differenceTick < (1000 / FPS)) {
			SDL_Delay((1000 / FPS) - differenceTick);
		}
	}


}

void Game::stopGame() {
	loopActive = false;
}

TTF_Font* Game::getFont() {
	return font;
}

void Game::changeFont(TTF_Font* font) {
	this->font = font;
}