#pragma once

#include "Actor.h"

/**
* Class that represents the celestial ray that the angel can use 1 time in each level
*/
class CelestialRay : public Actor
{
public:
	CelestialRay(float x, float y, Game* game);
	void update();

private:
	int vx;
};


