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
	incrementY(axis*50);
	
}



