#include "CelestialRay.h"

CelestialRay::CelestialRay(float x, float y, Game* game) :
	Actor("res/world/CelestialRay.png", x, y, 27, 19, game) {
	vx = -9;
}

void CelestialRay::update() {
	x = x + vx;
}

