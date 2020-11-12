#include "Cookie.h"

Cookie::Cookie(int pathX, int pathY, Game* game)
	: Movable(getRandomCookie(), 15, 16, pathX, pathY, game) {

}
void Cookie::update() {
	if (!getIsMoving()) {
		move();
	}
}
void Cookie::addLife(TheGirl* girl) {
	girl->getOneLife();
}
void Cookie::move() {
	x = x - 1;
	if (x < getPathX() * PATH_X) {
		pathX--;
	}
}

string Cookie::getRandomCookie() {
	int cookie = (rand() % 6) + 1; //from 1 to 7
	return "res/cookies/cookie_" + to_string(cookie) + ".png";
}
