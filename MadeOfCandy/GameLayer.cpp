#include "GameLayer.h"


GameLayer::GameLayer(Game* game) : Layer(game) {
	init();
}

void GameLayer::init() {
	background = new Background("res/world/City.png", WIDTH * 0.5, HEIGHT * 0.5,-1, getGame());

	menuLayer = (MenuLayer*)(getGame()->getMenuLayer());

	buttonGrab = new Actor("res/interface/grab_button.png", WIDTH * 0.75, HEIGHT * 0.85,80,80,0, 0, getGame());
	buttonShoot = new Actor("res/interface/shoot_button.png", WIDTH * 0.91, HEIGHT * 0.74,80,80, 0, 0, getGame());
	pad = new Pad(WIDTH * 0.15, HEIGHT * 0.80, getGame());

	finals.clear();
	enemies.clear();
	movables.clear();
	cookies.clear();
	loadMap("res/world/maps/" + to_string(getGame()->getCurrentLevel()) + ".txt");

	rayIcon = new Actor("res/icons/CelestialRayIcon.png",
		WIDTH * 0.05, HEIGHT * 0.05, 34, 31, 0, 0, getGame());


	controlShoot = false;
	controlMoveElement = false;
	controlMoveY = 0;
	controlMoveX = 0;

	bool elementCaught = false; 
	if (getGame()->getCurrentLevel() == 0) {
		textLifes = new Text("", WIDTH * 0.92, HEIGHT * 0.04, getGame());
		lifes = new Actor("res/icons/heart.png",
			WIDTH * 0.85, HEIGHT * 0.05, 24, 24, 0, 0, getGame());

		recolectableIcon = new Actor("res/icons/recolectableIcon.png",
			WIDTH * 0.13, HEIGHT * 0.05, 25, 25, 0, 0, getGame());
		textRecolectable= new Text("", WIDTH * 0.18, HEIGHT * 0.04, getGame());

		textCaught = new Text("Element caught", WIDTH * 0.50, HEIGHT * 0.04, getGame());

		audioBackground = new Audio("res/music/Candy.mp3", true);
		audiogetRecolectable = new Audio("res/music/effects/GirlAddLife.wav", false);
		audioBackground->play();
	}

	textRecolectable->content = "x" + to_string(numberOfGainedRecolectables);
	textLifes->content = to_string(girl->getLife());

}

void GameLayer::processControls() {
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
	if (controlShoot) {
		rayIcon = new Actor("res/icons/NoCelestialRayIcon.png",
			WIDTH * 0.05, HEIGHT * 0.05, 34, 31, 0, 0, getGame());
		angel->shoot(controlShoot);
		controlShoot = false;
	}
	if (controlMoveElement) {
		elementCaught = angel->moveElement(controlMoveElement, movables);
		controlMoveElement = false;
	}
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
	background->update();
	angel->update();
	girl->update();

	for (auto const& enemy : enemies) {
		enemy->update();
	}

	for (auto const& cookie : cookies) {
		cookie->update();
	}

	for (auto const& f : finals) {
		f->update();
	}

	if (currentRecolectable != nullptr) {
		currentRecolectable->update();
		if (girl->isOverlap(currentRecolectable) && !currentRecolectable->getIsMoving()) {
			audiogetRecolectable->play();

			numberOfGainedRecolectables++;
			textRecolectable->content = "x" + to_string(numberOfGainedRecolectables);
			gainedRecolectables[getGame()->getCurrentLevel()] = true;
			delete currentRecolectable;
			currentRecolectable = nullptr;
		}
	}


	enemyColisions();
	cookieColisions();
	finalOfLevelCollision();
}

void GameLayer::draw() {
	background->draw();

	if (elementCaught) {
		textCaught->draw();
	}

	angel->draw();
	girl->draw();

	for (auto const& enemy : enemies) {
		enemy->draw();
	}

	for (auto const& cookie : cookies) {
		cookie->draw();
	}

	for (auto const& f : finals) {
		f->draw();
	}

	if (currentRecolectable != nullptr) {
		currentRecolectable->draw();
	}

	lifes->draw();
	textLifes->draw();

	rayIcon->draw();

	recolectableIcon->draw();
	textRecolectable->draw();

	if (getGame()->getInputType() == INPUTMOUSE) {
		buttonGrab->draw();
		buttonShoot->draw();
		pad->draw();
	}

	SDL_RenderPresent(getGame()->getRenderer()); 
}

void GameLayer::keysToControls(SDL_Event event) {

	if (event.type == SDL_KEYDOWN) {
		int code = event.key.keysym.sym;

		switch (code) {
		case SDLK_ESCAPE:
			getGame()->setLayer(menuLayer);
			break;
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


void GameLayer::mouseToControls(SDL_Event event) {

	float motionX = event.motion.x;
	float motionY = event.motion.y;
	if (event.type == SDL_MOUSEBUTTONDOWN) {
		if (buttonShoot->containsPoint(motionX, motionY)) {
			controlShoot = true;
		}
		if (buttonGrab->containsPoint(motionX, motionY)) {
			controlMoveElement = true;
		}
		if (pad->containsPoint(motionX, motionY)) {
			pad->clicked = true;
			//Y
			controlMoveY = pad->getOrientationY(motionY);
			cout << controlMoveY;
			if (controlMoveY > -20 && controlMoveY < 20) {
				controlMoveY = 0;
			}
			else if (controlMoveY > 0) {
				controlMoveY = 1;
			}
			else {
				controlMoveY = -1;
			}
			//X
			controlMoveX = pad->getOrientationX(motionX);
			if (controlMoveX > -20 && controlMoveX < 20) {
				controlMoveX = 0;
			}
			else if (controlMoveX > 0) {
				controlMoveX = 1;
			}
			else {
				controlMoveX = -1;
			}
		}

	}
	else if(event.type == SDL_MOUSEMOTION){
		if (pad->clicked && pad->containsPoint(motionX, motionY)) {
			//Y
			controlMoveY = pad->getOrientationY(motionY);
			if (controlMoveY > -20 && controlMoveY < 20) {
				controlMoveY = 0;
			}
			else if (controlMoveY > 0) {
				controlMoveY = 1;
			}
			else {
				controlMoveY = -1;
			}
			//X
			controlMoveX = pad->getOrientationX(motionX);

			if (controlMoveX > -20 && controlMoveX < 20) {
				controlMoveX = 0;
			}
			else if (controlMoveX > 0) {
				controlMoveX = 1;
			}
			else {
				controlMoveX = -1;
			}
		}//if contains point
	}
		else {
		pad->clicked = false; // han sacado el rat�n del pad
			controlMoveX = 0;
		}
}



void GameLayer::enemyColisions() {
	list<Enemy*> deleteEnemies;

	//girl and enemy
	for (auto const& enemy : enemies) {
		if (girl->isOverlap(enemy) && !enemy->getIsMoving()) {
				enemy->attack(girl, angel);
				enemy->beShoot();
				textLifes->content = to_string(girl->getLife());
				if (girl->isDead()) {
					init();
					break;
				}
			}
		bool eInList = std::find(deleteEnemies.begin(),
			deleteEnemies.end(),
			enemy) != deleteEnemies.end();

		if (!eInList) {
			deleteEnemies.push_back(enemy);
		}
	}

	//enemy and ray
	if (angel->getRay() != nullptr) {
		for (auto const& enemy : enemies) {
			if (enemy->isOverlap(angel->getRay())) {
				enemy->beShoot();
			}
			bool eInList = std::find(deleteEnemies.begin(),
				deleteEnemies.end(),
				enemy) != deleteEnemies.end();

			if (!eInList) {
				deleteEnemies.push_back(enemy);
			}
		}//for
	}//if


	for (auto const& delEnemy : deleteEnemies) {
		if (delEnemy->beDeleted()) {
			enemies.remove(delEnemy);
		}
	}
	deleteEnemies.clear();

}

void GameLayer::cookieColisions() {
	list<Cookie*> deleteCookies;

	//girl and cookie
	for (auto const& cookie : cookies) {
		if (girl->isOverlap(cookie) && !cookie->getIsMoving()) {
			cookie->addLife(girl);
			textLifes->content = to_string(girl->getLife());

			bool eInList = std::find(deleteCookies.begin(),
				deleteCookies.end(),
				cookie) != deleteCookies.end();

			if (!eInList) {
				deleteCookies.push_back(cookie);
			}
		}
	}


	for (auto const& delCookie : deleteCookies) {
			cookies.remove(delCookie);
			delete delCookie;
	}
	deleteCookies.clear();

}

void GameLayer::finalOfLevelCollision() {

	for (auto const& f : finals) {
		if (girl->isOverlap(f)) {
			cout << "next level game\n";
			int newLevel = getGame()->getCurrentLevel() + 1;
			getGame()->setCurrentLevel(newLevel);
			if (newLevel == LEVELS) {
				cout << "Finished game\n";
			}
				init();
				return;
		}
	}


}


void GameLayer::loadMap(string name) {
	char character;
	string line;
	ifstream streamFile(name.c_str());
	if (!streamFile.is_open()) {
		cout << "Error opening map" << endl;
		return;
	}
	else {

		for (int i = 0; getline(streamFile, line); i++) {
			istringstream streamLine(line);
			mapWidth = line.length() * PATH_X;

			for (int j = 0; !streamLine.eof(); j++) {
				streamLine >> character; 
				loadMapObject(character, j+1, i+1);
			}
		}
	}
	streamFile.close();
}


void GameLayer::loadMapObject(char character, float x, float y) {
	switch (character) {
	case '1': {
		girl = new TheGirl(numberGirl,60, 0.2, x, y, getGame());
		break;
	}
	case '2': {
		angel = new Angel(numberAngel,x, y, getGame());
		break;
	}
	case 'b': {
		Enemy* enemy = new Blob(x, y, getGame());
		enemies.push_back(enemy);
		movables.push_back(enemy);
		break;
	}
	case 'C':{
		Cookie* cookie = new Cookie(x, y, getGame());
		cookies.push_back(cookie);
		movables.push_back(cookie);
		break;
	}
	case 'R': {
		if (gainedRecolectables[getGame()->getCurrentLevel()] == false) {
			currentRecolectable = new Recolectable("res/recolectables/recolectable_" + to_string(getGame()->getCurrentLevel()) + ".png", x, y, getGame());
			movables.push_back(currentRecolectable);
		}
		else {
			currentRecolectable = nullptr;
		}
		break;
	}
	case 'F': {
		finals.push_back(new FinalOfLevel(x,y,getGame()));
		break;
	}
	}
}

void GameLayer::setNumberGirl(int numberGirl) {
	this->numberGirl = numberGirl;
}
void GameLayer::setNumberAngel(int numberAngel) {
	this->numberAngel = numberAngel;
}

int GameLayer::getNumberGirl() {
	return numberGirl;
}
int GameLayer::getNumberAngel() {
	return numberAngel;
}







