#include "Jasper.h"

Jasper::Jasper(int pathX, int pathY, Game* game) 
	: Enemy("", 1, 40, 40, pathX, pathY, game) {

	aDie = new Animation("res/Enemies/Jasper/JasperDie.png", getWidth(), getHeight(),
		160, 40, 6, 4, false, game);
	aIdle = new Animation("res/Enemies/Jasper/JasperIdle.png", getWidth(), getHeight(),
		160, 40, 6, 4, true, game);
	animation = aIdle;

	canBeDeleted = false;
}
void Jasper::update() {
	if (animation->update()) {
		canBeDeleted = true;
	}
	if (!getIsMoving()) {
		move();
	}
}
void Jasper::draw() {
	animation->draw(x, y);
}

void Jasper::attack(TheGirl* girl, Angel* angel) {
	if (!dead) {
		girl->loseLife(1);
	}
}
void Jasper::beShoot() {
	dead = true;
	animation = aDie;
}
