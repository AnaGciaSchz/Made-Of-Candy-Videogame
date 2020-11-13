#include "FinalOfLevel.h"

FinalOfLevel::FinalOfLevel(int pathX, int pathY, Game* game)
	:Actor("res/world/finalOfLevel.png",34,31, pathX, pathY, game) {
}
void FinalOfLevel::update() {
	x = x - 1;
	if (x < getPathX() * PATH_X) {
		pathX--;
	}
}