#include "MenuLayer.h"

#include "GameLayer.h"

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


	this->gameLayer = (GameLayer*)(getGame()->getGameLayer());

	selectGirl(1);
	selectAngel(1);


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
		gameLayer->init();
		getGame()->setLayer(gameLayer);
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
			case SDLK_k:
				editMode = false;
				break;
			case SDLK_1:
				selectGirl(1);
				break;
			case SDLK_2:
				selectGirl(2);
				break;
			case SDLK_3:
				selectGirl(3);
				break;
			case SDLK_a:
				selectAngel(1);
				break;
			case SDLK_b:
				selectAngel(2);
				break;
			case SDLK_c:
				selectAngel(3);
				break;
			}
		}
	}
}

void MenuLayer::selectGirl(int numberGirl) {
	if (numberGirl == 1) {
		gameLayer->setNumberGirl(1);
		editGirl1 = new Actor("res/interface/editButtons/EditGirl_1Selected.png", WIDTH * 0.55, HEIGHT * 0.6, 31, 55, 0, 0, getGame());
		editGirl2 = new Actor("res/interface/editButtons/EditGirl_2.png", WIDTH * 0.65, HEIGHT * 0.6, 31, 55, 0, 0, getGame());
		editGirl3 = new Actor("res/interface/editButtons/EditGirl_3.png", WIDTH * 0.75, HEIGHT * 0.6, 31, 55, 0, 0, getGame());
	}
	else if (numberGirl == 2) {
		gameLayer->setNumberGirl(2);
		editGirl1 = new Actor("res/interface/editButtons/EditGirl_1.png", WIDTH * 0.55, HEIGHT * 0.6, 31, 55, 0, 0, getGame());
		editGirl2 = new Actor("res/interface/editButtons/EditGirl_2Selected.png", WIDTH * 0.65, HEIGHT * 0.6, 31, 55, 0, 0, getGame());
		editGirl3 = new Actor("res/interface/editButtons/EditGirl_3.png", WIDTH * 0.75, HEIGHT * 0.6, 31, 55, 0, 0, getGame());
	}
	else {
		gameLayer->setNumberGirl(3);
		editGirl1 = new Actor("res/interface/editButtons/EditGirl_1.png", WIDTH * 0.55, HEIGHT * 0.6, 31, 55, 0, 0, getGame());
		editGirl2 = new Actor("res/interface/editButtons/EditGirl_2.png", WIDTH * 0.65, HEIGHT * 0.6, 31, 55, 0, 0, getGame());
		editGirl3 = new Actor("res/interface/editButtons/EditGirl_3Selected.png", WIDTH * 0.75, HEIGHT * 0.6, 31, 55, 0, 0, getGame());
	}
}

void MenuLayer::selectAngel(int numberAngel) {
	if (numberAngel == 1) {
		gameLayer->setNumberAngel(1);
		editAngel1 = new Actor("res/interface/editButtons/EditAngel_1Selected.png", WIDTH * 0.55, HEIGHT * 0.4, 31, 55, 0, 0, getGame());
		editAngel2 = new Actor("res/interface/editButtons/EditAngel_2.png", WIDTH * 0.65, HEIGHT * 0.4, 31, 55, 0, 0, getGame());
		editAngel3 = new Actor("res/interface/editButtons/EditAngel_3.png", WIDTH * 0.75, HEIGHT * 0.4, 31, 55, 0, 0, getGame());
	}
	else if (numberAngel == 2){
		gameLayer->setNumberAngel(2);
		editAngel1 = new Actor("res/interface/editButtons/EditAngel_1.png", WIDTH * 0.55, HEIGHT * 0.4, 31, 55, 0, 0, getGame());
		editAngel2 = new Actor("res/interface/editButtons/EditAngel_2Selected.png", WIDTH * 0.65, HEIGHT * 0.4, 31, 55, 0, 0, getGame());
	    editAngel3 = new Actor("res/interface/editButtons/EditAngel_3.png", WIDTH * 0.75, HEIGHT * 0.4, 31, 55, 0, 0, getGame());
	}
	else {
		gameLayer->setNumberAngel(3);
		editAngel1 = new Actor("res/interface/editButtons/EditAngel_1.png", WIDTH * 0.55, HEIGHT * 0.4, 31, 55, 0, 0, getGame());
		editAngel2 = new Actor("res/interface/editButtons/EditAngel_2.png", WIDTH * 0.65, HEIGHT * 0.4, 31, 55, 0, 0, getGame());
		editAngel3 = new Actor("res/interface/editButtons/EditAngel_3Selected.png", WIDTH * 0.75, HEIGHT * 0.4, 31, 55, 0, 0, getGame());
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

			if (editGirl1->containsPoint(motionX, motionY)) {
				selectGirl(1);
			}

			if (editGirl2->containsPoint(motionX, motionY)) {
				selectGirl(2);
			}

			if (editGirl3->containsPoint(motionX, motionY)) {
				selectGirl(3);
			}

			if (editAngel1->containsPoint(motionX, motionY)) {
				selectAngel(1);
			}

			if (editAngel2->containsPoint(motionX, motionY)) {
				selectAngel(2);
			}

			if (editAngel3->containsPoint(motionX, motionY)) {
				selectAngel(3);
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

		editGirl1->draw();
		editGirl2->draw();
		editGirl3->draw();

		editAngel1->draw();
		editAngel2->draw();
		editAngel3->draw();
	}

	SDL_RenderPresent(getGame()->getRenderer());
}
