#include "MenuLayer.h"

MenuLayer::MenuLayer(Game* game)
	: Layer(game) {
	init();
}

void MenuLayer::init() {

	backgroundMenu = new Background("res/interface/Menu.png", WIDTH * 0.5, HEIGHT * 0.5, getGame());
	playButton = new Actor("res/interface/Menu_playButton.png", WIDTH * 0.5, HEIGHT * 0.4, 106, 54, 0,0,getGame());
	editButton = new Actor("res/interface/Menu_editButton.png", WIDTH * 0.5, HEIGHT * 0.6, 106, 54, 0,0,getGame());
	exitButton = new Actor("res/interface/Menu_exitButton.png", WIDTH * 0.5, HEIGHT * 0.8, 106, 54, 0,0,getGame());
	backButton = new Actor("res/interface/Menu_editBackButton.png", WIDTH * 0.7, HEIGHT * 0.8, 106, 54, 0, 0, getGame());

	backgroundEdit = new Background("res/interface/Menu_edit.png", WIDTH * 0.5, HEIGHT * 0.5, getGame());

	editMode = false;
	controlContinue = false;
}



void MenuLayer::processControls() {

	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		if (event.type == SDL_QUIT) {
			getGame()->stopGame();
		}
		if (event.type == SDL_KEYDOWN) {
			getGame()->setInputType(INPUTKEYBOARD);
		}
		if (event.type == SDL_MOUSEBUTTONDOWN) {
			getGame()->setInputType(INPUTMOUSE);
		}

		if (getGame()->getInputType() == INPUTKEYBOARD) {
			keysToControls(event);
		}
		if (getGame()->getInputType() == INPUTMOUSE) {
			mouseToControls(event);
		}
	}

	if (controlContinue) {
		getGame()->setLayer(getGame()->getGameLayer());
		controlContinue = false;
	}
}


void MenuLayer::keysToControls(SDL_Event event) {
	if (event.type == SDL_KEYDOWN) {
		int code = event.key.keysym.sym;
		if (!editMode) {
			switch (code) {
			case SDLK_ESCAPE:
				getGame()->stopGame();
				break;
			case SDLK_SPACE:
				controlContinue = true;
				break;
			case SDLK_p:
				controlContinue = true;
				break;
			case SDLK_x:
				getGame()->stopGame();
				break;
			case SDLK_e:
				editMode = true;
				break;
			}
		}else{//editMode
			switch (code) {
			case SDLK_ESCAPE:
				getGame()->stopGame();
				break;
			case SDLK_SPACE:
				editMode = false;
				break;
			case SDLK_b:
				editMode = false;
				break;
			}
		}
	}
}

void MenuLayer::mouseToControls(SDL_Event event) {
	float motionX = event.motion.x;
	float motionY = event.motion.y;

	if (event.type == SDL_MOUSEBUTTONDOWN) {
		if (!editMode) {
			if (playButton->containsPoint(motionX, motionY)) {
				controlContinue = true;
			}
			if (exitButton->containsPoint(motionX, motionY)) {
				getGame()->stopGame();
			}
			if (editButton->containsPoint(motionX, motionY)) {
				editMode = true;
			}
		}
		else {//editMode
			if (backButton->containsPoint(motionX, motionY)) {
				editMode = false;
			}
		}
	}
}






void MenuLayer::draw() {
	if (!editMode) {
		backgroundMenu->draw();
		playButton->draw();
		editButton->draw();
		exitButton->draw();
	}
	else {
		backgroundEdit->draw();
		backButton->draw();
	}

	SDL_RenderPresent(getGame()->getRenderer());
}
