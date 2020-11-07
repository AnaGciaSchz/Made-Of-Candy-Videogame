#pragma once

#include "Actor.h"
#include "CelestialRay.h"

/**
* Class that represents the Angel (the player)
*/
class Angel : public Actor
{
public:
	Angel(float x, float y, Game* game);

	void update();
	void drawAngel ();
	void shoot(bool shoot);
	//void moveElement(bool move);
	void moveX(float axis);
	void moveY(float axis);
	void cantShoot();

private:
	bool canShoot;
	CelestialRay* ray;
};
