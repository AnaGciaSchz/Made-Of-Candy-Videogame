#include "Enemy.h"

Enemy::Enemy(string filename,float x, float y, int damage, int width, int height, Game* game)
	: Actor(filename, x, y, width, height, game) {

	this->damage = damage;
	this->dead = false;
}

void Enemy::update() {
	
}

bool Enemy::isDead() {
	return dead;
}

int Enemy::getDamage() {
	return damage;
}

void Enemy::move(int x, int y) {
	this->x = x;
	this->y = y;
}

