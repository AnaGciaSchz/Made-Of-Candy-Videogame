#include "Halloween.h"

Halloween::Halloween(int pathX, int pathY, Game* game) 
	: Enemy("", 1, 30, 35, pathX, pathY, game) {
	getRandomHalloween();

	animation = aIdle;

	canBeDeleted = false;
}
void Halloween::update() {
	if (animation->update()) {
		canBeDeleted = true;
	}
	if (!getIsMoving()) {
		move();
	}
}
void Halloween::draw() {
	animation->draw(x, y);
}

void Halloween::attack(TheGirl* girl, Angel* angel) {
	if (!dead) {
		girl->loseLife(1);
		angel->paralyzed();
	}
}
void Halloween::beShoot() {
	dead = true;
	animation = aDie;
}

void Halloween::getRandomHalloween() {
	int number = (rand() % 2) + 1; //from 1 to 2
	if (number == 1) {
		aDie = new Animation("res/Enemies/Halloween/Reaper/ReaperDie.png", getWidth(), getHeight(),
			90, 29, 6, 3, false, getGame());
		aIdle = new Animation("res/Enemies/Halloween/Reaper/ReaperIdle.png", getWidth(), getHeight(),
			90, 29, 6, 3, true, getGame());
	}
	else {
		aDie = new Animation("res/Enemies/Halloween/Witch/witchDie.png", getWidth(), getHeight(),
			101, 40, 6, 4, false, getGame());
		aIdle = new Animation("res/Enemies/Halloween/Witch/witchIdle.png", getWidth(), getHeight(),
			101, 40, 6, 4, true, getGame());
	}
}
