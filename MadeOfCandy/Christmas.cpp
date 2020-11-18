#include "Christmas.h"

Christmas::Christmas(int pathX, int pathY, Game* game)
	: Enemy("", 1, 30, 35, pathX, pathY, game) {
	getRandomChristmas();

	animation = aIdle;

	canBeDeleted = false;
}
void Christmas::update() {
	if (animation->update()) {
		canBeDeleted = true;
	}
	if (!getIsMoving()) {
		move();
	}
}
void Christmas::draw() {
	animation->draw(x, y);
}

void Christmas::attack(TheGirl* girl, Angel* angel) {
	if (!dead) {
		girl->loseLife(1);
		angel->cantShoot();
	}
}
void Christmas::beShoot() {
	dead = true;
	animation = aDie;
}

void Christmas::getRandomChristmas() {
	int number = (rand() % 2) + 1; //from 1 to 2
	if (number == 1) {
		aDie = new Animation("res/Enemies/Christmas/Fernando/FernandoDie.png", getWidth(), getHeight(),
			78, 29, 6, 3, false, getGame());
		aIdle = new Animation("res/Enemies/Christmas/Fernando/FernandoIdle.png", getWidth(), getHeight(),
			78, 29, 6, 3, true, getGame());
	}
	else {
		aDie = new Animation("res/Enemies/Christmas/Santa/SantaDie.png", getWidth(), getHeight(),
			78, 31, 6, 3, false, getGame());
		aIdle = new Animation("res/Enemies/Christmas/Santa/SantaIdle.png", getWidth(), getHeight(),
			78, 31, 6, 3, true, getGame());
	}
}
