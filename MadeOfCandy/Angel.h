#pragma once

#include "Actor.h"
#include "CelestialRay.h"
#include "Audio.h"
#include "Animation.h" 

/**
* Class that represents the Angel (the player)
*/
class Angel : public Actor
{
public:
	Angel(float pathX, float pathY, Game* game);

	void update();
	void draw() override;
	void shoot(bool shoot);
	//void moveElement(bool move);
	void moveX(float axis);
	void moveY(float axis);
	void cantShoot();
	void deleteRay();

	CelestialRay* getRay();

private:
	bool canShoot;
	CelestialRay* ray;

	Animation* aLeftUp;
	Animation* aRightUp;
	Animation* aLeft;
	Animation* aRight;
	Animation* animation;

	Audio* audioRay;
};
