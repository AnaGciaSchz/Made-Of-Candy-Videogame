#include "CelestialRay.h"

CelestialRay::CelestialRay(float pathX, float pathY,int time, Game* game) :
	Actor("res/world/CelestialRay.png", 27, 19,pathX,pathY, game) {
	time = time;
	actualTime = 0;
}

void CelestialRay::update() {
	actualTime--;
	if (actualTime <= 0) {
		actualTime = time;
		incrementX(-1);
	}
}

