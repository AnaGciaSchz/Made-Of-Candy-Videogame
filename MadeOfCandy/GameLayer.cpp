#include "GameLayer.h"


GameLayer::GameLayer(Game* game) : Layer(game) {
	init();
}

void GameLayer::init() {
	//angel = new Angel(PATHS_X-1, PATHS_Y / 2, getGame());
	//girl = new TheGirl(60,0.2,0,PATHS_Y/2, getGame());
	background = new Background("res/world/City.png", WIDTH * 0.5, HEIGHT * 0.5,-1, getGame());

	loadMap("res/world/maps/0.txt");

	textLifes = new Text("", WIDTH * 0.92, HEIGHT * 0.04, getGame());
	textLifes->content = to_string(girl->getLife());
	lifes = new Actor("res/icons/heart.png",
		WIDTH * 0.85, HEIGHT * 0.05, 24, 24,0,0, getGame());

	controlShoot = false;
	controlMoveElement = false;
	controlMoveY = 0;
	controlMoveX = 0;

	tiles.clear();
	enemies.clear(); 
	//enemies.push_back(new Blob(5, 1, getGame()));
	//enemies.push_back(new Blob(5, 2, getGame()));
	//enemies.push_back(new Blob(5, 3, getGame()));
	//enemies.push_back(new Blob(5, 4, getGame()));
	//enemies.push_back(new Blob(5, 5, getGame()));

	audioBackground = new Audio("res/music/Candy.mp3", true);
	audioBackground->play();

}

void GameLayer::processControls() {
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		keysToControls(event);
	}
	angel->shoot(controlShoot);
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
	background->update();
	angel->update();
	girl->update();

	for (auto const& enemy : enemies) {
		enemy->update();
	}

	enemyColisions();
}

void GameLayer::draw() {
	background->draw();

	lifes->draw();
	textLifes->draw();

	angel->draw();
	girl->draw();

	for (auto const& tile : tiles) {
		tile->draw();
	}

	for (auto const& enemy : enemies) {
		enemy->draw();
	}

	SDL_RenderPresent(getGame()->getRenderer()); 
}

void GameLayer::keysToControls(SDL_Event event) {
	if (event.type == SDL_QUIT) {
		getGame()->stopGame();
	}

	if (event.type == SDL_KEYDOWN) {
		int code = event.key.keysym.sym;

		switch (code) {
		case SDLK_ESCAPE:
			getGame()->stopGame();
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

void GameLayer::enemyColisions() {
	list<Enemy*> deleteEnemies;

	//girl and enemy
	for (auto const& enemy : enemies) {
		if (girl->isOverlap(enemy)) {
				enemy->attack(girl, angel);
				enemy->beShoot();
				textLifes->content = to_string(girl->getLife());
				if (girl->isDead()) {
					init();
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


void GameLayer::loadMapObject(char character, float x, float y)
{
	switch (character) {
	case '1': {
		girl = new TheGirl(60, 0.2, x, y, getGame());
		break;
	}
	case '2': {
		angel = new Angel(x, y, getGame());
		break;
	}
//	case '#': {
//		Tile* tile = new Tile("res/bloque_tierra.png", x, y, game);
//		// modificación para empezar a contar desde el suelo.
//		tile->y = tile->y - tile->height / 2;
//		tiles.push_back(tile);
//		break;
//	}
	}
}







