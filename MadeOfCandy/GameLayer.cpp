#include "GameLayer.h"


GameLayer::GameLayer(Game* game) : Layer(game) {
	initializeTextAndIcons();

	initializeAudio();
	audioBackground->play();

	reinit();	
	init();
}

void GameLayer::init() {
	if (controlFinish) {
		reinit();		
		getGame()->setLayer(getGame()->getMenuLayer());
	}
	background = new Background("res/world/City.png", WIDTH * 0.5, HEIGHT * 0.5,-1, getGame());

	menuLayer = (MenuLayer*)(getGame()->getMenuLayer());

	initializeInterface();
	

	emptyLists();
	loadMap("res/world/maps/" + to_string(getGame()->getCurrentLevel()) + ".txt");

	rayIcon = new Actor("res/icons/CelestialRayIcon.png",
		WIDTH * 0.05, HEIGHT * 0.05, 34, 31, 0, 0, getGame());

	initializeControls();

	bool elementCaught = false; 

	textRecolectable->content = "x" + to_string(numberOfGainedRecolectables);
	textLifes->content = to_string(girl->getLife());

	showMessages();

}

void GameLayer::processControls() {
	if (canProcess) {
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

		continueMessage();

		controlPlayer();

	}//canProcess
}

void GameLayer::update() {
	waitMessage();
	if (pause) {
		return;
	}

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

	updateRecolectable();

	//We need to see if the icon of the angel is showing the correct information
	if (!angel->getCanShoot()) {
		rayIcon = new Actor("res/icons/NoCelestialRayIcon.png",
			WIDTH * 0.05, HEIGHT * 0.05, 34, 31, 0, 0, getGame());
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

	if (getGame()->getInputType() == INPUTMOUSE && !pause) {
		buttonGrab->draw();
		buttonShoot->draw();
		pad->draw();
	}

	if (pause) {
		pausePlayIcon = new Actor("res/icons/PlayIcon.png",
			WIDTH * 0.95, HEIGHT * 0.05, 29, 26, 0, 0, getGame());
		pausePlayIcon->draw();
		message->draw();
	}
	else {
		pausePlayIcon = new Actor("res/icons/PauseIcon.png",
			WIDTH * 0.95, HEIGHT * 0.05, 29, 26, 0, 0, getGame());
		pausePlayIcon->draw();
	}

	SDL_RenderPresent(getGame()->getRenderer()); 
}

void GameLayer::keysToControls(SDL_Event event) {

	if (event.type == SDL_KEYDOWN) {
		if (pause) {
			controlContinue = true;
		}
		int code = event.key.keysym.sym;

		switch (code) {
		case SDLK_ESCAPE:
			audioReturnToMenu->play();
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
		case SDLK_p:
			pause = !pause;
			break;
		}
	}
}


void GameLayer::mouseToControls(SDL_Event event) {

	float motionX = event.motion.x;
	float motionY = event.motion.y;

	if (event.type == SDL_MOUSEBUTTONDOWN) {
		if (pause) {
			controlContinue = true;
		}
		if (pausePlayIcon->containsPoint(motionX, motionY)) {
			pause = !pause;
		}
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
		pad->clicked = false; // the mouse is not in the pad
			controlMoveX = 0;
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
		girl = new TheGirl(numberGirl, 60, 0.2, x, y, getGame());
		break;
	}
	case '2': {
		angel = new Angel(numberAngel, x, y, getGame());
		break;
	}
	case 'b': {
		Enemy* enemy = new Blob(x, y, getGame());
		enemies.push_back(enemy);
		movables.push_back(enemy);
		break;
	}
	case 'o': {
		Enemy* enemy = generateObstacle(x, y);
		enemies.push_back(enemy);
		movables.push_back(enemy);
		break;
	}
	case 'J': {
		Enemy* enemy = new Jasper(x, y, getGame());
		enemies.push_back(enemy);
		movables.push_back(enemy);
		break;
	}
	case 'h': {
		Enemy* enemy = new Halloween(x, y, getGame());
		enemies.push_back(enemy);
		movables.push_back(enemy);
		break;
	}
	case 'c': {
		Enemy* enemy = new Christmas(x, y, getGame());
		enemies.push_back(enemy);
		movables.push_back(enemy);
		break;
	}
	case 'B': {
		Enemy* enemy = new BlobMinion(x, y, getGame());
		enemies.push_back(enemy);
		movables.push_back(enemy);
		break;
	}
	case 'C': {
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
		finals.push_back(new FinalOfLevel(x, y, getGame()));
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

/////////////////////////////////////////////////////PRIVATE METHODS/////////////////////////////////////////////////////

void GameLayer::reinit() {
	controlFinish = false;
	controlContinue = false;

	getGame()->setCurrentLevel(0);

	pause = true;
	canProcess = false;

	countMessages = 1;
	message = new Actor("res/interface/howToPlay.png", WIDTH * 0.5, HEIGHT * 0.5,
		WIDTH, HEIGHT, 0, 0, getGame());

	gainedRecolectables = { false,false,false,false,false };
	numberOfGainedRecolectables = 0;
}

void GameLayer::emptyLists() {
	finals.clear();
	enemies.clear();
	movables.clear();
	cookies.clear();
}
void GameLayer::showMessages() {
	if (getGame()->getCurrentLevel() == 1 && countMessages == 3) {
		message = new Actor("res/interface/EnemyMessage/JasperMessage.png", WIDTH * 0.5, HEIGHT * 0.5,
			WIDTH, HEIGHT, 0, 0, getGame());
		countMessages++;
		controlContinue = false;
	}
	else if (getGame()->getCurrentLevel() == 2 && countMessages == 4) {
		message = new Actor("res/interface/EnemyMessage/HalloweenMessage.png", WIDTH * 0.5, HEIGHT * 0.5,
			WIDTH, HEIGHT, 0, 0, getGame());
		countMessages++;
		controlContinue = false;
	}
	else if (getGame()->getCurrentLevel() == 3 && countMessages == 5) {
		message = new Actor("res/interface/EnemyMessage/ChristmasMessage.png", WIDTH * 0.5, HEIGHT * 0.5,
			WIDTH, HEIGHT, 0, 0, getGame());
		countMessages++;
		controlContinue = false;
	}
	else if (getGame()->getCurrentLevel() == 4 && countMessages == 6) {
		message = new Actor("res/interface/EnemyMessage/BlobMinionMessage.png", WIDTH * 0.5, HEIGHT * 0.5,
			WIDTH, HEIGHT, 0, 0, getGame());
		countMessages++;
		controlContinue = false;
	}
}

void GameLayer::initializeControls() {
	controlFinish = false;
	controlShoot = false;
	controlMoveElement = false;
	controlMoveY = 0;
	controlMoveX = 0;
}

void GameLayer::initializeInterface() {
	buttonGrab = new Actor("res/interface/grab_button.png", WIDTH * 0.75, HEIGHT * 0.85, 80, 80, 0, 0, getGame());
	buttonShoot = new Actor("res/interface/shoot_button.png", WIDTH * 0.91, HEIGHT * 0.74, 80, 80, 0, 0, getGame());
	pad = new Pad(WIDTH * 0.15, HEIGHT * 0.80, getGame());
}

Enemy* GameLayer::generateObstacle(int x, int y) {
	int number = (rand() % 5) + 1;
	if (number == 1) {
		return new Obstacle("res/Enemies/Obstacle/box.png", 11, 17, x, y, getGame());
	}
	else if (number == 2) {
		return new Obstacle("res/Enemies/Obstacle/ligth.png", 16, 46, x, y, getGame());
	}
	else if (number == 3) {
		return new Obstacle("res/Enemies/Obstacle/plant.png", 16, 16, x, y, getGame());
	}
	else if (number == 4) {
		return new Obstacle("res/Enemies/Obstacle/plug.png", 14, 15, x, y, getGame());
	}
	else {
		return new Obstacle("res/Enemies/Obstacle/signal.png", 24, 23, x, y, getGame());
	}
}

void GameLayer::continueMessage() {
	if (controlContinue) {
		if (getGame()->getCurrentLevel() == 0) {
			if (countMessages == 1) {
				message = new Actor("res/interface/EnemyMessage/ObstacleMessage.png", WIDTH * 0.5, HEIGHT * 0.5,
					WIDTH, HEIGHT, 0, 0, getGame());
				countMessages++;
				controlContinue = false;
			}
			else if (countMessages == 2) {
				message = new Actor("res/interface/EnemyMessage/BlobMessage.png", WIDTH * 0.5, HEIGHT * 0.5,
					WIDTH, HEIGHT, 0, 0, getGame());
				countMessages++;
				controlContinue = false;
			}
			else {
				pause = false;
				controlContinue = false;
			}
		}
		else if (countMessages == 8) {
			controlFinish = true;
			pause = false;
			controlContinue = false;
			init();
		}
		else {
			pause = false;
			controlContinue = false;
		}
	}
}


void GameLayer::controlPlayer() {
	if (controlShoot) {
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

void GameLayer::initializeAudio() {
	audioBackground = new Audio("res/music/Candy.mp3", true);
	audiogetRecolectable = new Audio("res/music/effects/Recolectable.wav", false);
	audioReturnToMenu = new Audio("res/music/effects/Cancel.wav", false);
}

void GameLayer::initializeTextAndIcons() {
	textLifes = new Text("", WIDTH * 0.9, HEIGHT * 0.05, getGame());
	lifes = new Actor("res/icons/heart.png",
		WIDTH * 0.85, HEIGHT * 0.05, 24, 24, 0, 0, getGame());

	recolectableIcon = new Actor("res/icons/recolectableIcon.png",
		WIDTH * 0.13, HEIGHT * 0.05, 25, 25, 0, 0, getGame());
	textRecolectable = new Text("", WIDTH * 0.18, HEIGHT * 0.04, getGame());

	textCaught = new Text("Element caught", WIDTH * 0.50, HEIGHT * 0.04, getGame());
}

void GameLayer::waitMessage() {
	if (canProcess == false && canProcessTime != 0) {
		canProcessTime--;
	}
	else if (canProcess == false && canProcessTime == 0) {
		canProcess = true;
		canProcessTime = 15;
	}
}

void GameLayer::updateRecolectable() {
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
			pause = true;
			canProcess = false;
			int newLevel = getGame()->getCurrentLevel() + 1;
			getGame()->setCurrentLevel(newLevel);
			if (newLevel == LEVELS) {
				if (numberOfGainedRecolectables == 5) {
					message = new Actor("res/interface/WonRecolectables.png", WIDTH * 0.5, HEIGHT * 0.5,
						WIDTH, HEIGHT, 0, 0, getGame());
					countMessages = 8;
				}
				else {
					message = new Actor("res/interface/Won.png", WIDTH * 0.5, HEIGHT * 0.5,
						WIDTH, HEIGHT, 0, 0, getGame());
					countMessages = 8;
				}
			}
			init();
			return;
		}
	}


}








