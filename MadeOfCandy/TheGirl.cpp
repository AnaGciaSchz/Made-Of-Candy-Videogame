#include "TheGirl.h"

TheGirl::TheGirl(int timeY, int timeX,int v, int pathX, int pathY, Game* game)
	: Actor("res/characters/TheGirl/Anna.png", 23, 46,pathX,pathY, game) {
	this->timeY = timeY;
	this->actualTimeY = timeY;

	this->timeX = timeX;
	this->actualTimeX = timeX;

	this->lifes = 3;
	
	this->v = v;
}

void TheGirl::update() {
	actualTimeY--;
	if (actualTimeY <= 0) {
		actualTimeY = timeY;
		if (rand() > RAND_MAX / 2) {
			moveY();
		}
	}

	actualTimeX--;
	if (actualTimeX <= 0) {
		actualTimeX = timeX;
		incrementX(1);
	}

}
void TheGirl::moveY() {
	int value;
	if (getPathY()<=1){ 
		incrementY(1);
	}
	else if (getPathY() >= PATHS_Y) {
		incrementY(-1);
	}
	else {
		incrementY((rand() > RAND_MAX / 2) ? 1 : -1);
	}

}

void TheGirl::loseLife(int damage) {
	lifes -= damage;
}

int TheGirl::getLife() {
	return lifes;
}

bool TheGirl::isDead() {
	if (lifes <= 0) {
		return true;
	}
	return false;
}
