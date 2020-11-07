#include "TheGirl.h"

TheGirl::TheGirl(float x, float y, int time, Game* game)
	: Actor("res/characters/TheGirl/Anna.png", x, y, 23, 46, game) {
	this->time = time;
	this->actualTime = time;

	this->lifes = 3;
}

void TheGirl::update() {
	actualTime--;
	x = x + 1;
	if (actualTime <= 0) {
		actualTime = time;
		moveY();
	}

}
void TheGirl::moveY() {
	int value;
	if (y -50 - getHeight() / 2 <= 0){ 
		value = 50;
	}
	else if (y +50 + getHeight() / 2 >= HEIGHT) {
		value = -50;
	}
	else {
		value = (rand() > RAND_MAX / 2) ? -50 : 50;
	}

	incrementY(value);
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
