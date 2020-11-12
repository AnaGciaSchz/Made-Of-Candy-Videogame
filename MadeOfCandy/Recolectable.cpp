#include "Recolectable.h"

Recolectable::Recolectable(string filename,int pathX, int pathY, Game* game)
	: Movable(filename, 15, 16, pathX, pathY, game) {

}
void Recolectable::update() {
	if (!getIsMoving()) {
		move();
	}
}
void Recolectable::addLife(TheGirl* girl) {
	girl->addLife(2);
}
void Recolectable::move() {
	x = x - 1;
	if (x < getPathX() * PATH_X) {
		pathX--;
	}
}
