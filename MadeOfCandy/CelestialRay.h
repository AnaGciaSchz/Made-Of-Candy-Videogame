#pragma once

#include "Actor.h"

/**
* Class that represents the celestial ray that the angel can use 1 time in each level
*/
class CelestialRay : public Actor
{
public:
	CelestialRay(float pathX, float pathY,int time, Game* game);
	void update();

private:
	int time;
	int actualTime;
};


