#include "Blob.h"

Blob::Blob(int pathX, int pathY, Game* game)
	: Enemy("", 1, 64, 61,pathX,pathY, game) {

	aDie = new Animation("res/Enemies/Blob/blob_die.png", getWidth(), getHeight(),
		640, 80, 6, 8, game);
	aIdle = new Animation("res/Enemies/Blob/blob_idle.png", getWidth(), getHeight(),
		640, 80, 6, 8, game);
	animation = aIdle;

}
void Blob::attack(TheGirl* girl, Angel* angel) {
	if (!dead) {
		girl->loseLife(1);
	}
}
void Blob::beShoot() {
	dead = true;
	animation = aDie;
}

void Blob::update() {
	animation->update();
	move();
}

void Blob::draw() {
	animation->draw(x, y);
}
