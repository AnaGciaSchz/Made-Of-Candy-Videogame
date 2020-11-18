#include "Obstacle.h"

Obstacle::Obstacle(string filename, int widthImage, int heightImage,int pathX, int pathY, Game* game)
	: Enemy(filename, 1, widthImage, heightImage, pathX, pathY, game){

	canBeDeleted = false;
}

void Obstacle::update() {
	if (!getIsMoving()) {
		move();
	}
}

void Obstacle::attack(TheGirl* girl, Angel* angel) {
	if (!dead) {
		girl->loseLife(1);
	}
}

void Obstacle::beShoot() {
	dead = true;
	canBeDeleted = true;
}

