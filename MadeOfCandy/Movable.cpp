#include "Movable.h"

Movable::Movable(string filename, int width, int height, int pathX, int pathY, Game* game) 
	:Actor(filename, width, height, pathX, pathY, game) {
	isBeingMoved = false;
}

void Movable::move(int incrementX, int incrementY) {
		Actor::incrementX(incrementX);
		Actor::incrementY(incrementY);

}

void Movable::moveObject(bool move) {
	isBeingMoved = move;
}
bool Movable::getIsMoving() {
	return isBeingMoved;
}
