#include "Angel.h"

Angel::Angel(float pathX, float pathY, Game* game)
	: Actor("res/characters/Angel/Robbie.png", 23, 46,pathX, pathY, game) {

	canShoot = true;
	ray = nullptr;

	audioRay = new Audio("res/music/effects/Ray.wav", false);
}

void Angel::update() {
	if (ray != nullptr) {
		ray->update();
		deleteRay();
	}
}

void Angel::moveX(float axis) {
	if (axis > 0 && getPathX() == PATHS_X) {
		
	}
	else if (axis < 0 && getPathX() == 0) {
		
	}
	else {
		incrementX(axis);
	}
	
}

void Angel::moveY(float axis) {
	if (axis > 0 && getPathY() == PATHS_Y) {
	}
	else if (axis < 0 && getPathY() == 1) {
	}
	else {
		incrementY(axis);
	}
	
}

void Angel::shoot(bool shoot) {
	if (shoot && canShoot) {
		audioRay->play();
		cantShoot();
		ray = new CelestialRay(getPathX(),getPathY(),30,getGame());
	}
}

CelestialRay* Angel::getRay() {
	return ray;
}

void Angel::cantShoot() {
	canShoot = false;
}

void Angel::deleteRay() {
	if (ray->isInRender()==false) {
		delete ray;
		ray = nullptr;
	}
}

void Angel::drawAngel() {
	draw();
	if (ray != nullptr) {
		ray->draw();
	}

}



