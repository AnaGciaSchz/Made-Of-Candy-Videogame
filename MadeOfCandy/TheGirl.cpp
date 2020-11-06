#include "TheGirl.h"

TheGirl::TheGirl(float x, float y, int time, Game* game)
	: Actor("res/characters/TheGirl/Anna.png", x, y, 23, 46, game) {
	this->time = time;
	this->actualTime = time;
}

void TheGirl::update() {
	actualTime--;
	if (actualTime <= 0) {
		actualTime = time;
		moveY();
	}

}
void TheGirl::moveY() {
	int value = (rand() > RAND_MAX / 2) ? -50 : 50;
	incrementY(value);
}
