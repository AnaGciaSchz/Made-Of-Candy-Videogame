#include "BlobMinion.h"

BlobMinion::BlobMinion(int pathX, int pathY, Game* game)
	: Enemy("", 2, 36, 37, pathX, pathY, game) {

	aIdle = new Animation("res/Enemies/BlobMinion/blobMinion.png", getWidth(), getHeight(),
		216, 37, 4, 6, true, game);

	canBeDeleted = false;

}
void BlobMinion::attack(TheGirl* girl, Angel* angel) {
		girl->loseLife(2);
}
void BlobMinion::beShoot() {
}

void BlobMinion::update() {
	if (!getIsMoving()) {
		move();
	}
}

void BlobMinion::draw() {
	aIdle->draw(x, y);
}
