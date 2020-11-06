#include "Angel.h"

Angel::Angel(float x, float y, Game* game)
	: Actor("res/characters/Angel/Robbie.png", x, y, 23, 46, game) {

}

void Angel::update() {
	
}

void Angel::moveX(float axis) {

	incrementX(axis*50);
}

void Angel::moveY(float axis) {
	int value;
	if (y + axis * 50 - getHeight() / 2 <= 0) {
		value = -axis * 50;
	}
	else if (y + axis * 50 + getHeight() / 2 >= HEIGHT) {
		value = -axis * 50;
	}
	else {
		value = axis * 50;
	}
	incrementY(value);
	
}



