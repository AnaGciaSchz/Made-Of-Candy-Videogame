#include "Enemy.h"

Enemy::Enemy(string filename, int damage, int width, int height, int pathX, int pathY, Game* game)
	: Movable(filename, width, height, pathX, pathY, game) {

	this->damage = damage;
	this->dead = false;

	this->canBeDeleted = false;
}

bool Enemy::isDead() {
	return dead;
}

int Enemy::getDamage() {
	return damage;
}
void Enemy::move() {
	x = x - 1;
	if (x < getPathX() * PATH_X) {
		pathX--;
	}
}

bool Enemy::beDeleted() {
	return this->canBeDeleted;
}


