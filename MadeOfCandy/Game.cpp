
#include "Game.h"
#include "MenuLayer.h"

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

	//set window icon
	SDL_Surface* surface = IMG_Load("res/cookies/cookie_5.png");
	SDL_SetWindowIcon(window, surface);
	SDL_FreeSurface(surface);

	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");

	gameLayer = new GameLayer(this);
	menuLayer = new MenuLayer(this);

	layer = menuLayer;

	TTF_Init();
	changeFont(TTF_OpenFont("res/fonts/monogram.ttf", 24));

	currentLevel = 0;

	loopActive = true;
	loop();
}

void Game::setLayer(Layer* layer) {
	this->layer = layer;
}
Layer* Game::getGameLayer() {
	return gameLayer;
}
Layer* Game::getMenuLayer() {
	return menuLayer;
}

void Game::loop() {
	//for the fps
	int initTick;
	int endTick;
	int differenceTick;
	while (loopActive) {
		initTick = SDL_GetTicks();

		// get the controls 
		layer->processControls();
		// update elements
		layer->update();
		// draw
		layer->draw();

		endTick = SDL_GetTicks();
		differenceTick = endTick - initTick;

		// To respect trhe fps
		if (differenceTick < (1000 / FPS)) {
			SDL_Delay((1000 / FPS) - differenceTick);
		}
	}

}

void Game::setInputType(int input) {
	this->input = input;
}

int Game::getInputType() {
	return input;
}

int Game::getCurrentLevel() {
	return currentLevel;
}
void Game::setCurrentLevel(int level) {
	this->currentLevel = level;
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

SDL_Texture* Game::getTexture(string filename) {
	if (mapTextures.find(filename) != mapTextures.end()) {
	}
	else {
		SDL_Surface* surface = IMG_Load(filename.c_str());
		SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
		mapTextures[filename] = texture;
	}

	return mapTextures[filename];
}
